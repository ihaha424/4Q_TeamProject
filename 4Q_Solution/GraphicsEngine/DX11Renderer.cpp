#include "pch.h"
#include "Animator.h"
#include "Camera.h"
#include "DX11Renderer.h"
#include "Filter.h"
#include "Light.h"
#include "Material.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Model.h"
#include "PixelShader.h"
#include "SkeletalMeshRenderer.h"
#include "SkyBoxRenderer.h"
#include "VertexShader.h"
#include "VIBuffer.h"

#include "CameraSystem.h"
#include "LightSystem.h"
#include "StructuredBuffer.h"

void DX11Renderer::Initialize()
{
	_pDeviceContext = g_pGraphicDevice->GetDeviceContext();

	_matrices.resize(MAX_DRAW_OBJECT);
	_boneMatrices.resize(MAX_DRAW_OBJECT * MAX_BONE_MATRIX);
	_directionalLights.resize(MAX_DIRECTIONAL_LIGHT);
	_pointLights.resize(MAX_POINT_LIGHT);

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
	const auto& renderData = g_pRenderGroup->GetRenderDatas();
	
	std::list<DrawData> alphaMeshes, noneAlphaMeshs;
	std::list<SkyBoxRenderer*> skyBoxes;

	unsigned int ID = 0;
	for (const auto& [component, matrix] : renderData)
	{
		if (!component->IsActiveDraw())
			continue;

		auto& model = component->GetModel();
		_matrices[ID] = XMMatrixTranspose(*matrix);

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
			continue;
		}

		const unsigned int mask = component->GetPostEffectFlag();

		for (auto& mesh : model->_meshs)
		{			
			if (mesh->_pMaterial->IsAlpha())
			{
				alphaMeshes.emplace_back(ID, mask, mesh);
			}
			else
			{
				noneAlphaMeshs.emplace_back(ID, mask, mesh);
			}
		}

		ID++;
	}

	// Alpha Sort
	// meshes[RenderType::Alpha].sort();
	// NoneAlpha Sort
	// meshes[RenderType::NoneAlpha].sort();

	auto& lights = g_pLightSystem->GetLights();
	unsigned int numLight[GE::ILight::End]{};
	
	for (auto& light : lights)
	{
		switch (light->GetType())
		{
		case GE::ILight::Directional:
			if (numLight[GE::ILight::Directional] >= MAX_DIRECTIONAL_LIGHT)
				continue;
			_directionalLights[numLight[GE::ILight::Directional]++] = light->_lightData;
			break;
		case GE::ILight::Point:
			if (numLight[GE::ILight::Point] >= MAX_POINT_LIGHT)
				continue;
			_pointLights[numLight[GE::ILight::Point]++] = light->_lightData;
			break;
		case GE::ILight::Spot:
			break;
		}
	}

	// Lights
	g_pConstantBuffer->UpdateConstantBuffer(L"DirectionalLights", _directionalLights.data());
	g_pConstantBuffer->UpdateConstantBuffer(L"PointLights", _pointLights.data());
	g_pConstantBuffer->UpdateConstantBuffer(L"NumLight", numLight);

	// Matrices
	g_pStructuredBuffer->UpdateStructuredBuffer(L"WorldMatrices", _matrices.data());
	g_pStructuredBuffer->UpdateStructuredBuffer(L"BoneMatrices", _boneMatrices.data());
	g_pStructuredBuffer->SetStructuredBuffer(L"WorldMatrices", ShaderType::Vertex, 0, 1);
	g_pStructuredBuffer->SetStructuredBuffer(L"BoneMatrices", ShaderType::Vertex, 1, 1);

	// ResetState
	_pDeviceContext->OMSetDepthStencilState(nullptr, 0XFF);

	ShadowPass();
	
	_pDeviceContext->PSSetShaderResources(10, 1, &_pShadowSRV);	
	DeferredPass(noneAlphaMeshs);
	ForwardPass(alphaMeshes);
	
	ID3D11ShaderResourceView* nullSRV = nullptr;
	_pDeviceContext->PSSetShaderResources(10, 1, &nullSRV);
	
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
	Camera* pCamera = g_pCameraSystem->GetCurrentCamera();
	Light* pMainLight = g_pLightSystem->GetMainLight();

	float dist = 7000.f;
	XMVECTOR direction = XMVector3Normalize(-pMainLight->_lightData.data);
	XMVECTOR lightPosition = direction * dist + XMVectorSet(0.f, dist, 0.f, 0.f);
	XMVECTOR lightTarget = direction;
	XMVECTOR lightUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX view = XMMatrixLookAtLH(lightPosition, lightTarget, lightUp);

	float viewWidth = SHADOW_WIDTH;
	float viewHeight = SHADOW_HEIGHT;
	float nearPlane = dist;
	float farPlane = 10000.0f;

	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PIDIV4, 1, nearPlane, farPlane);
	
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

	SetViewport(SHADOW_WIDTH, SHADOW_HEIGHT);
	_pDeviceContext->OMSetRenderTargets(0, nullptr, _pShadowDSV);
	_pDeviceContext->ClearDepthStencilView(_pShadowDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	_pDeviceContext->PSSetShader(nullptr, nullptr, 0);

	const auto& renderDatas = g_pRenderGroup->GetRenderDatas();
	auto prevType = MeshType::End;
	unsigned int offset[2]{ 0, MAX_BONE_MATRIX };

	unsigned int ID = 0;
	for (auto& [component, matrix] : renderDatas)
	{
		if (!component->IsActiveShadow())
			continue;

		auto type = component->GetType();
		if (prevType != type)
		{
			_vsShadow[(int)type]->SetVertexShader();
			prevType = type;
		}

		std::shared_ptr<Model>& model = component->GetModel();

		offset[0] = ID++;
		for (auto& mesh : model->_meshs)
		{
			g_pConstantBuffer->UpdateConstantBuffer(L"ModelIndex", &offset);
			mesh->_pVIBuffer->SetParameters(_pDeviceContext);
			mesh->_pVIBuffer->DrawIndexed(_pDeviceContext);
		}
	}

	// Directional Pass
	// Point Pass
	// Spot Pass
	_pDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
}

void DX11Renderer::DeferredPass(std::list<DrawData>& renderData)
{
	SetViewport(g_width, g_height);

	auto& [RTVs, SRVs] = g_pViewManagement->GetRenderTargetGroup(L"Deferred");
	unsigned int numTargets = (unsigned int)RTVs.size();

	_pDeviceContext->OMSetRenderTargets(numTargets, RTVs.data(), _pDefaultDSV);
	_pDeviceContext->OMSetBlendState(_pDeferredBlendState, NULL, 0xFFFFFFFF);
	_pDeviceContext->ClearDepthStencilView(_pDefaultDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
	for (unsigned int i = 0; i < numTargets; i++) _pDeviceContext->ClearRenderTargetView(RTVs[i], COLOR_ZERO);

	RenderMesh(renderData, _psGBuffer);
	SSAOPass();

	auto* pRTV = g_pViewManagement->GetRenderTargetView(L"Base");

	_pDeviceContext->OMSetRenderTargets(1, &pRTV, nullptr);
	_pDeviceContext->ClearRenderTargetView(pRTV, COLOR_ZERO);

	// Diffuse, Normal, Specular, Emissive, ShadowPosition, Depth
	_pDeviceContext->PSSetShaderResources(0, End, SRVs.data());
	_pDeviceContext->PSSetShaderResources(5, 1, &_pDefaultSRV);

	_psDeferredLighting->SetPixelShader();
	g_pQuad->Render();

	ID3D11ShaderResourceView* nullSRV[End + 1]{ nullptr, };
	_pDeviceContext->PSSetShaderResources(0, End + 1, nullSRV);
}

void DX11Renderer::ForwardPass(std::list<DrawData>& renderData)
{
	float blendFactor[4]{ 0.f, 0.f, 0.f, 0.f };

	auto& [RTVs, SRVs] = g_pViewManagement->GetRenderTargetGroup(L"Forward");

	_pDeviceContext->OMSetRenderTargets((unsigned int)RTVs.size(), RTVs.data(), _pDefaultDSV);
	_pDeviceContext->OMSetBlendState(_pForwardBlendState, blendFactor, 0xFFFFFFFF);	
	RenderMesh(renderData, _psForwardLighting);

	_pDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
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

void DX11Renderer::SSAOPass()
{

}

void DX11Renderer::PostProcessing()
{	
	auto& [RTVs, SRVs] = g_pViewManagement->GetRenderTargetGroup(L"Blend");
	auto* pBaseSRV = g_pViewManagement->GetShaderResourceView(L"Base");
	auto* pLayerMaskSRV = g_pViewManagement->GetShaderResourceView(L"LayerMask");
	auto* pPostProcessRTV = g_pViewManagement->GetRenderTargetView(L"PostProcess");
	unsigned int currentIndex = 0;		

	ID3D11ShaderResourceView* pSRV = nullptr;
	_pDeviceContext->PSSetShaderResources(0, 1, &pBaseSRV);
	_pDeviceContext->PSSetShaderResources(1, 1, &pLayerMaskSRV);

	auto& filters = g_pPostProcessSystem->GetFilters();
	for (auto& [mask, filter] : filters)
	{
		g_pConstantBuffer->UpdateConstantBuffer(L"LayerMask", &mask);

		filter->Render();
		BlendPass(RTVs[currentIndex], pSRV);
		pSRV = SRVs[currentIndex];
		currentIndex = (currentIndex + 1) % 2;
				
		pSRV = g_pViewManagement->GetShaderResourceView(L"PostProcess");
	}

	_pDeviceContext->OMSetBlendState(NULL, NULL, 0xFFFFFFF);

	// ToneMapping
	auto* pBackBuffer = g_pGraphicDevice->GetBackBuffer();

	_pDeviceContext->OMSetRenderTargets(1, &pBackBuffer, nullptr);
	_pDeviceContext->ClearRenderTargetView(pBackBuffer, COLOR_ZERO);
	_pDeviceContext->PSSetShaderResources(2, 1, &SRVs[currentIndex]);
	_psToneMapping->SetPixelShader();
	g_pQuad->Render();

	// Reset
	ID3D11ShaderResourceView* nullSRVs[2]{ nullptr, };
	_pDeviceContext->PSSetShaderResources(0, 2, nullSRVs);
}

void DX11Renderer::BlendPass(ID3D11RenderTargetView* pRTV, ID3D11ShaderResourceView* pSRV)
{
	auto* pPostSRV = g_pViewManagement->GetShaderResourceView(L"PostProcess");
	ID3D11ShaderResourceView* nullSRV = nullptr;

	_pDeviceContext->PSSetShaderResources(2, 1, &nullSRV);
	_pDeviceContext->OMSetRenderTargets(1, &pRTV, nullptr);
	_pDeviceContext->PSSetShaderResources(2, 1, &pSRV);
	_pDeviceContext->PSSetShaderResources(3, 1, &pPostSRV);
	_psBlend->SetPixelShader();
	g_pQuad->Render();
}

void DX11Renderer::RenderMesh(std::list<DrawData>& renderData, std::shared_ptr<PixelShader>& pixelShader)
{
	pixelShader->SetPixelShader();

	unsigned int offset[2]{ 0, MAX_BONE_MATRIX };
	unsigned int layerMask = 0;
	for (auto& [ID, mask, mesh] : renderData)
	{
		offset[0] = ID;
		layerMask = mask;
		g_pConstantBuffer->UpdateConstantBuffer(L"ModelIndex", &offset);
		g_pConstantBuffer->UpdateConstantBuffer(L"LayerMask", &layerMask);

		mesh->SetVertexShader();
		mesh->_pVIBuffer->SetParameters(_pDeviceContext);
		mesh->_pMaterial->SetParameters(pixelShader);
		mesh->_pVIBuffer->DrawIndexed(_pDeviceContext);
	}
}

void DX11Renderer::InitState()
{
	ID3D11Device* pDevice = g_pGraphicDevice->GetDevice();

	D3D11_RENDER_TARGET_BLEND_DESC enableRTBD
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

	D3D11_RENDER_TARGET_BLEND_DESC disableRTBD
	{
		.BlendEnable = FALSE,
		.SrcBlend = D3D11_BLEND_SRC_ALPHA,
		.DestBlend = D3D11_BLEND_INV_SRC_ALPHA,
		.BlendOp = D3D11_BLEND_OP_ADD,
		.SrcBlendAlpha = D3D11_BLEND_ONE,
		.DestBlendAlpha = D3D11_BLEND_ZERO,
		.BlendOpAlpha = D3D11_BLEND_OP_ADD,
		.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL
	};

	D3D11_BLEND_DESC forwardDesc{};
	forwardDesc.IndependentBlendEnable = TRUE;
	forwardDesc.RenderTarget[0] = enableRTBD;
	forwardDesc.RenderTarget[1] = disableRTBD;

	pDevice->CreateBlendState(&forwardDesc, &_pForwardBlendState);
	
	D3D11_BLEND_DESC deferredDesc{};
	deferredDesc.RenderTarget[0] = disableRTBD;
	deferredDesc.RenderTarget[1] = disableRTBD;
	deferredDesc.RenderTarget[2] = disableRTBD;
	deferredDesc.RenderTarget[3] = disableRTBD;
	deferredDesc.RenderTarget[4] = disableRTBD;
	deferredDesc.RenderTarget[5] = disableRTBD;
	pDevice->CreateBlendState(&deferredDesc, &_pDeferredBlendState);

	D3D11_RASTERIZER_DESC rsDesc
	{
		.FillMode = D3D11_FILL_SOLID,
		.CullMode = D3D11_CULL_NONE,
		.DepthClipEnable = FALSE,
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

	g_pViewManagement->AddRenderTargetView(L"Base", Vector2(g_width, g_height));

	g_pViewManagement->AddRenderTargetView(L"Diffuse", Vector2(g_width, g_height));
	g_pViewManagement->AddRenderTargetView(L"Normal", Vector2(g_width, g_height));
	g_pViewManagement->AddRenderTargetView(L"Specular", Vector2(g_width, g_height));
	g_pViewManagement->AddRenderTargetView(L"Emissive", Vector2(g_width, g_height));
	g_pViewManagement->AddRenderTargetView(L"ShadowPosition", Vector2(g_width, g_height));

	g_pViewManagement->AddRenderTargetView(L"LayerMask", Vector2(g_width, g_height), DXGI_FORMAT_R32_UINT);
	g_pViewManagement->AddRenderTargetView(L"PostProcess", Vector2(g_width, g_height));

	g_pViewManagement->AddRenderTargetGroup(L"Deferred", L"Diffuse");
	g_pViewManagement->AddRenderTargetGroup(L"Deferred", L"Normal");
	g_pViewManagement->AddRenderTargetGroup(L"Deferred", L"Specular");
	g_pViewManagement->AddRenderTargetGroup(L"Deferred", L"Emissive");
	g_pViewManagement->AddRenderTargetGroup(L"Deferred", L"ShadowPosition");
	g_pViewManagement->AddRenderTargetGroup(L"Deferred", L"LayerMask");

	g_pViewManagement->AddRenderTargetGroup(L"Forward", L"Base");
	g_pViewManagement->AddRenderTargetGroup(L"Forward", L"LayerMask");

	g_pViewManagement->AddRenderTargetView(L"Blend0", Vector2(g_width, g_height));
	g_pViewManagement->AddRenderTargetView(L"Blend1", Vector2(g_width, g_height));

	g_pViewManagement->AddRenderTargetGroup(L"Blend", L"Blend0");
	g_pViewManagement->AddRenderTargetGroup(L"Blend", L"Blend1");
}

void DX11Renderer::InitShader()
{
	_vsShadow[MeshType::Static] = g_pResourceMgr->LoadResource<VertexShader>(L"../Resources/Shaders/ShadowVS.cso");
	_vsShadow[MeshType::Skeletal] = g_pResourceMgr->LoadResource<VertexShader>(L"../Resources/Shaders/ShadowVS_Skeletal.cso");	

	_psForwardLighting = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/ForwardLightingPS.cso");
	_psDeferredLighting = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/DeferredLightingPS.cso");
	_psGBuffer = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/GBufferPS.cso");
	_psBlend = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/BlendPS.cso");
	_psToneMapping = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/ToneMappingPS.cso");
}

void DX11Renderer::InitDepthStencil()
{
	D3D11_TEXTURE2D_DESC textureDesc
	{
		.Width = (unsigned int)g_width,
		.Height = (unsigned int)g_height,
		.MipLevels = 1,
		.ArraySize = 1,
		.Format = DXGI_FORMAT_D24_UNORM_S8_UINT,
		.SampleDesc {.Count = 1 },
		.Usage = D3D11_USAGE_DEFAULT,
		.BindFlags = D3D11_BIND_DEPTH_STENCIL,
	};

	D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc
	{
		.Format = textureDesc.Format,
		.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D,
	};
	
	g_pViewManagement->AddDepthStencilView(L"Default", textureDesc, dsvDesc);

	textureDesc.Width = (unsigned int)SHADOW_WIDTH;
	textureDesc.Height = (unsigned int)SHADOW_HEIGHT;
	textureDesc.BindFlags |= D3D11_BIND_SHADER_RESOURCE;
	textureDesc.Format = DXGI_FORMAT_R32_TYPELESS;
	dsvDesc.Format = DXGI_FORMAT_D32_FLOAT;

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
	SafeRelease(_pDeferredBlendState);
	SafeRelease(_pForwardBlendState);
}