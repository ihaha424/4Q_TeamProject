#include "pch.h"
#include "DX11Renderer.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "MeshRenderer.h"
#include "SkeletalMeshRenderer.h"
#include "SkyBoxRenderer.h"
#include "Animator.h"
#include "Model.h"
#include "Mesh.h"
#include "Camera.h"
#include "VIBuffer.h"
#include "Material.h"
#include "Light.h"

void DX11Renderer::Initialize()
{
	_pDeviceContext = g_pGraphicDevice->GetDeviceContext();

	_matrices.resize(MAX_DRAW_OBJECT);
	_boneMatrices.resize(MAX_DRAW_OBJECT * MAX_BONE_MATRIX);
	_directionalLights.resize(8);
	_pointLights.resize(64);

	// Viewport
	_viewport.MaxDepth = 1.f;

	// Shader
	InitShader();

	// MRT
	InitMRT();

	// DepthStencil
	InitDepthStencil();

	// StructuredBuffer
	InitStructuredBuffer();

	// Optional
	InitOptional();
	
	// State
	InitState();
}

void DX11Renderer::Render()
{
	Camera* pCamera = g_pCameraSystem->GetCurrentCamera();

	XMVECTOR direction = XMVector3Normalize(-Vector3(1.f, 0.f, 1.f));
	XMVECTOR lightPosition = direction * 5000.f + XMVectorSet(0.f, 5000.f, 0.f, 0.f);
	XMVECTOR lightTarget = direction;
	XMVECTOR lightUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX view = XMMatrixLookAtLH(lightPosition, lightTarget, lightUp);

	float viewWidth = SHADOW_WIDTH;
	float viewHeight = SHADOW_HEIGHT;
	float nearPlane = 1.f;
	float farPlane = 10000.0f;

	XMMATRIX proj = XMMatrixOrthographicLH(viewWidth, viewHeight, nearPlane, farPlane);
	
	ViewProjection vp
	{
		.vp = pCamera->GetViewMatrix() * pCamera->GetProjectionMatrix(),
		.shadowVP = XMMatrixTranspose(view * proj)
	};

	CameraDesc cameraDesc
	{
		.vpInvers = XMMatrixTranspose(XMMatrixInverse(nullptr, vp.vp)),
		.cameraPosition = pCamera->GetPosition(),
	};

	vp.vp = XMMatrixTranspose(vp.vp);

	g_pConstantBuffer->UpdateConstantBuffer(L"ViewProjection", &vp);
	g_pConstantBuffer->UpdateConstantBuffer(L"CameraDesc", &cameraDesc);

	const auto& renderData = g_pRenderGroup->GetRenderData();
	std::list<Mesh*> meshes[RenderType::End];
	std::list<SkyBoxRenderer*> skyBoxes;

	unsigned int ID = 0;
	for (const auto& [component, matrix] : renderData)
	{
		auto& model = component->GetModel();
		_matrices[ID] = XMMatrixTranspose(XMMATRIX(&matrix->_11));

		switch (component->GetType())
		{
		case MeshType::Skeletal:
		{
			Animator* pAnimator = static_cast<SkeletalMeshRenderer*>(component)->GetAnimator();
			memcpy(&_boneMatrices[ID * MAX_BONE_MATRIX], pAnimator->GetAnimationTransform().data(), sizeof(Matrix) * MAX_BONE_MATRIX);
			break;
		}
		case MeshType::SkyBox:
			skyBoxes.push_back(static_cast<SkyBoxRenderer*>(component));
			break;
		}

		for (auto& mesh : model->_meshs)
		{
			mesh->SetID(ID);
			
			if (mesh->_pMaterial->IsAlpha())
			{
				meshes[RenderType::Alpha].push_back(mesh);
			}
			else
			{
				meshes[RenderType::NoneAlpha].push_back(mesh);
			}
		}

		ID++;
	}

	// Alpha Sort
	// meshes[RenderType::Alpha].sort();
	// NoneAlpha Sort
	// meshes[RenderType::NoneAlpha].sort();

	auto& lights = g_pLightSystem->GetLights();
	unsigned int numLight[2]{};
	
	for (auto& light : lights)
	{
		switch (light->GetType())
		{
		case GE::ILight::Type::Directional:
			_directionalLights[numLight[0]++] = light->_lightData;
			break;
		case GE::ILight::Type::Point:
			_pointLights[numLight[1]++] = light->_lightData;
			break;
		}
	}

	g_pConstantBuffer->UpdateConstantBuffer(L"DirectionalLights", _directionalLights.data());
	g_pConstantBuffer->UpdateConstantBuffer(L"PointLights", _pointLights.data());
	g_pConstantBuffer->UpdateConstantBuffer(L"NumLight", numLight);

	g_pStructuredBuffer->UpdateStructuredBuffer(L"WorldMatrices", _matrices.data());
	g_pStructuredBuffer->UpdateStructuredBuffer(L"BoneMatrices", _boneMatrices.data());
	g_pStructuredBuffer->SetStructuredBuffer(L"WorldMatrices", ShaderType::Vertex, 0, 1);
	g_pStructuredBuffer->SetStructuredBuffer(L"BoneMatrices", ShaderType::Vertex, 1, 1);

	ShadowPass();
	DeferredPass(meshes[RenderType::NoneAlpha]);
	ForwardPass(meshes[RenderType::Alpha]);
	SkyBoxPass(skyBoxes);
	PostProcessing();
}

void DX11Renderer::SetViewport(float width, float height)
{
	_viewport.Width = width;
	_viewport.Height = height;
	_pDeviceContext->RSSetViewports(1, &_viewport);
}

void DX11Renderer::ShadowPass()
{
	SetViewport(SHADOW_WIDTH, SHADOW_HEIGHT);
	_pDeviceContext->OMSetRenderTargets(0, nullptr, _pShadowDSV);
	_pDeviceContext->ClearDepthStencilView(_pShadowDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	_pDeviceContext->PSSetShader(nullptr, nullptr, 0);

	const auto& renderData = g_pRenderGroup->GetRenderData();
	auto prevType = MeshType::End;
	unsigned int offset[2]{ 0, MAX_BONE_MATRIX };

	for (auto& [component, matrix] : renderData)
	{
		auto type = component->GetType();
		if (prevType != type)
		{
			_vsShadow[(int)type]->SetVertexShader();
			prevType = type;
		}

		std::shared_ptr<Model>& model = component->GetModel();

		for (auto& mesh : model->_meshs)
		{
			offset[0] = mesh->GetID();
			g_pConstantBuffer->UpdateConstantBuffer(L"ModelIndex", &offset);
			mesh->_pVIBuffer->SetParameters(_pDeviceContext);
			mesh->_pVIBuffer->DrawIndexed(_pDeviceContext);
		}
	}
}

void DX11Renderer::DeferredPass(std::list<Mesh*>& renderData)
{
	SetViewport(g_width, g_height);
	_pDeviceContext->OMSetBlendState(nullptr, nullptr, 0xFFFFFFFF);

	auto& [renderTargets, textures] = g_pViewManagement->GetRenderTargetGroup(L"Deferred");

	_pDeviceContext->OMSetRenderTargets((unsigned int)renderTargets.size(), renderTargets.data(), _pDefaultDSV);
	_pDeviceContext->ClearDepthStencilView(_pDefaultDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);

	float color[4]{ 0.0f, 0.0f, 0.0f, 1.f };
	for (int i = 0; i < End; i++)
		_pDeviceContext->ClearRenderTargetView(renderTargets[i], color);

	_psGBuffer->SetPixelShader();

	RenderMesh(renderData, _psGBuffer);	

	ID3D11RenderTargetView* pBlendTarget = g_pViewManagement->GetRenderTargetView(L"Blend");

	_pDeviceContext->OMSetRenderTargets(1, &pBlendTarget, nullptr);
	_pDeviceContext->ClearRenderTargetView(pBlendTarget, color);

	_vsQuad->SetVertexShader();
	_psDeferred->SetPixelShader();
	
	_pDeviceContext->PSSetShaderResources(0, End, textures.data());
	_pDeviceContext->PSSetShaderResources(5, 1, &_pDefaultSRV);
	_pDeviceContext->PSSetShaderResources(10, 1, &_pShadowSRV);

	g_pQuad->SetParameters(_pDeviceContext);
	g_pQuad->DrawIndexed(_pDeviceContext);

	ID3D11ShaderResourceView* nullSRV[End]{ nullptr, };
	_pDeviceContext->PSSetShaderResources(0, End, nullSRV);
	_pDeviceContext->PSSetShaderResources(5, 1, nullSRV);
	_pDeviceContext->PSSetShaderResources(10, 1, nullSRV);
}

void DX11Renderer::ForwardPass(std::list<Mesh*>& renderData)
{
	float blendFactor[4]{ 0.f, 0.f, 0.f, 0.f };
	ID3D11RenderTargetView* pBlendTarget = g_pViewManagement->GetRenderTargetView(L"Blend");

	_pDeviceContext->OMSetRenderTargets(1, &pBlendTarget, _pDefaultDSV);
	_pDeviceContext->OMSetBlendState(_pBlendState, blendFactor, 0xFFFFFFFF);

	_pDeviceContext->PSSetShaderResources(10, 1, &_pShadowSRV);
	_psLighting->SetPixelShader();

	RenderMesh(renderData, _psLighting);

	ID3D11ShaderResourceView* nullSRV = nullptr;
	_pDeviceContext->PSSetShaderResources(10, 1, &nullSRV);
}

void DX11Renderer::SkyBoxPass(std::list<SkyBoxRenderer*>& skyBoxes)
{
	_pDeviceContext->RSSetState(_pRSSkyBoxState);

	for (auto& component : skyBoxes)
	{
		component->Render(_pDeviceContext);
	}

	_pDeviceContext->RSSetState(nullptr);
}

void DX11Renderer::PostProcessing()
{
	ID3D11ShaderResourceView* pBlendTargetTexture = g_pViewManagement->GetShaderResourceView(L"Blend");
	ID3D11RenderTargetView* pBackBuffer = g_pGraphicDevice->GetBackBuffer();

	_pDeviceContext->OMSetRenderTargets(1, &pBackBuffer, nullptr);

	_vsQuad->SetVertexShader();
	_psBlend->SetPixelShader();

	_pDeviceContext->PSSetShaderResources(0, 1, &pBlendTargetTexture);
	g_pQuad->SetParameters(_pDeviceContext);
	g_pQuad->DrawIndexed(_pDeviceContext);
}

void DX11Renderer::RenderMesh(std::list<Mesh*>& renderData, std::shared_ptr<PixelShader>& pixelShader)
{
	unsigned int offset[2]{ 0, MAX_BONE_MATRIX };

	for (auto& mesh : renderData)
	{
		offset[0] = mesh->GetID();
		g_pConstantBuffer->UpdateConstantBuffer(L"ModelIndex", &offset);
		mesh->SetVertexShader();
		mesh->_pVIBuffer->SetParameters(_pDeviceContext);
		mesh->_pMaterial->SetParameters(pixelShader);
		mesh->_pVIBuffer->DrawIndexed(_pDeviceContext);
	}
}

void DX11Renderer::InitState()
{
	D3D11_BLEND_DESC blendDesc{};
	blendDesc.IndependentBlendEnable = true;
	blendDesc.RenderTarget[0] =
	{
		.BlendEnable = TRUE,
		.SrcBlend = D3D11_BLEND_SRC_ALPHA,
		.DestBlend = D3D11_BLEND_INV_SRC_ALPHA,
		.BlendOp = D3D11_BLEND_OP_ADD,
		.SrcBlendAlpha = D3D11_BLEND_ONE,
		.DestBlendAlpha = D3D11_BLEND_ZERO,
		.BlendOpAlpha = D3D11_BLEND_OP_ADD,
		.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL
	};

	ID3D11Device* pDevice = g_pGraphicDevice->GetDevice();
	pDevice->CreateBlendState(&blendDesc, &_pBlendState);

	D3D11_RASTERIZER_DESC rsDesc
	{
		.FillMode = D3D11_FILL_SOLID,
		.CullMode = D3D11_CULL_NONE,
		.DepthClipEnable = false,
	};

	pDevice->CreateRasterizerState(&rsDesc, &_pRSSkyBoxState);
}

void DX11Renderer::InitOptional()
{
	Vector4 texel = { 1.f / SHADOW_WIDTH, 0.f, 0.f, 0.f };
	g_pConstantBuffer->UpdateConstantBuffer(L"OptionalDesc", &texel);
}

void DX11Renderer::InitMRT()
{
	// Diffuse, Normal, Specular, Emissive, ShadowPosition;

	g_pViewManagement->AddRenderTargetView(L"Diffuse", Vector2(g_width, g_height));
	g_pViewManagement->AddRenderTargetView(L"Normal", Vector2(g_width, g_height));
	g_pViewManagement->AddRenderTargetView(L"Specular", Vector2(g_width, g_height));
	g_pViewManagement->AddRenderTargetView(L"Emissive", Vector2(g_width, g_height));
	g_pViewManagement->AddRenderTargetView(L"ShadowPosition", Vector2(g_width, g_height));

	g_pViewManagement->AddRenderTargetGroup(L"Deferred", L"Diffuse");
	g_pViewManagement->AddRenderTargetGroup(L"Deferred", L"Normal");
	g_pViewManagement->AddRenderTargetGroup(L"Deferred", L"Specular");
	g_pViewManagement->AddRenderTargetGroup(L"Deferred", L"Emissive");
	g_pViewManagement->AddRenderTargetGroup(L"Deferred", L"ShadowPosition");

	g_pViewManagement->AddRenderTargetView(L"Blend", Vector2(g_width, g_height));
}

void DX11Renderer::InitShader()
{
	_vsShadow[MeshType::Static] = g_pResourceMgr->LoadResource<VertexShader>(L"../Resources/Shaders/ShadowVS.cso");
	_vsShadow[MeshType::Skeletal] = g_pResourceMgr->LoadResource<VertexShader>(L"../Resources/Shaders/ShadowVS_Skeletal.cso");
	_vsQuad = g_pResourceMgr->LoadResource<VertexShader>(L"../Resources/Shaders/QuadVS.cso");

	_psDeferred = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/DeferredLightingPS.cso");
	_psGBuffer = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/GBufferPS.cso");
	_psLighting = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/ForwardLightingPS.cso");
	_psBlend = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/BlendPS.cso");
}

void DX11Renderer::InitDepthStencil()
{
	D3D11_TEXTURE2D_DESC textureDesc
	{
		.Width = (unsigned int)g_width,
		.Height = (unsigned int)g_height,
		.MipLevels = 1,
		.ArraySize = 1,
		.Format = DXGI_FORMAT_R32_TYPELESS,
		.SampleDesc {.Count = 1 },
		.Usage = D3D11_USAGE_DEFAULT,
		.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE,
	};

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc
	{
		.Format = DXGI_FORMAT_D32_FLOAT,
		.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D,
	};

	g_pViewManagement->AddDepthStencilView(L"Default", textureDesc, dsvDesc);

	textureDesc.Width = (unsigned int)SHADOW_WIDTH;
	textureDesc.Height = (unsigned int)SHADOW_HEIGHT;

	g_pViewManagement->AddDepthStencilView(L"Shadow", textureDesc, dsvDesc);

	_pDefaultDSV = g_pViewManagement->GetDepthStencilView(L"Default");
	_pDefaultSRV = g_pViewManagement->GetShaderResourceView(L"Default");
	_pShadowDSV = g_pViewManagement->GetDepthStencilView(L"Shadow");
	_pShadowSRV = g_pViewManagement->GetShaderResourceView(L"Shadow");
}

void DX11Renderer::InitStructuredBuffer()
{
	g_pStructuredBuffer->AddStructuredBuffer(L"WorldMatrices", sizeof(XMMATRIX) * MAX_DRAW_OBJECT, MAX_DRAW_OBJECT);
	g_pStructuredBuffer->AddStructuredBuffer(L"BoneMatrices", sizeof(XMMATRIX) * MAX_DRAW_OBJECT * MAX_BONE_MATRIX, MAX_DRAW_OBJECT * MAX_BONE_MATRIX);
}

void DX11Renderer::Free()
{
	SafeRelease(_pRSSkyBoxState);
	SafeRelease(_pBlendState);
}