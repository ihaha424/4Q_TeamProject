#include "pch.h"
#include "SkyBoxRenderer.h"
#include "StaticMesh.h"
#include "Texture.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Mesh.h"
#include "VIBuffer.h"

void SkyBoxRenderer::SetSkyBoxTexture(const wchar_t* filePath)
{
	_skyBox = g_pResourceMgr->LoadResource<Texture>(filePath);
}

void SkyBoxRenderer::SetBRDFTexture(const wchar_t* filePath)
{
	_textures[BRDF] = g_pResourceMgr->LoadResource<Texture>(filePath);
}

void SkyBoxRenderer::SetDiffuseTexture(const wchar_t* filePath)
{
	_textures[Diffsue] = g_pResourceMgr->LoadResource<Texture>(filePath);
}

void SkyBoxRenderer::SetSpecularTexture(const wchar_t* filePath)
{
	_textures[Specular] = g_pResourceMgr->LoadResource<Texture>(filePath);
}

void SkyBoxRenderer::SetIBLTextures(ID3D11DeviceContext* pDeviceContext)
{
	for (int i = 0; i < End;i++)
	{
		ID3D11ShaderResourceView* pSRV = nullptr;
		
		if (_textures[i].get())
			pSRV = _textures[i]->Get();

		pDeviceContext->PSGetShaderResources(11 + i, 1, &pSRV);
	}
}

void SkyBoxRenderer::Initialize(const wchar_t* filePath)
{
	_model = g_pResourceMgr->LoadResource<StaticMesh>(filePath);

	_vertexShader = g_pResourceMgr->LoadResource<VertexShader>(L"../Resources/Shaders/SkyBoxVS.cso");
	_pixelShader = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/SkyBoxPS.cso");
	_type = MeshType::SkyBox;

	_model->BindVertexShader(_vertexShader);
}

void SkyBoxRenderer::Render(ID3D11DeviceContext* pDeviceContext)
{
	ID3D11ShaderResourceView* pSRV = nullptr;

	if (_skyBox.get())
		pSRV = _skyBox->Get();

	pDeviceContext->PSGetShaderResources(0, 1, &pSRV);

	_vertexShader->SetVertexShader();
	_pixelShader->SetPixelShader();

	for (auto& mesh : _model->_meshs)
	{
		mesh->_pVIBuffer->SetParameters(pDeviceContext);
		mesh->_pVIBuffer->DrawIndexed(pDeviceContext);
	}
}
