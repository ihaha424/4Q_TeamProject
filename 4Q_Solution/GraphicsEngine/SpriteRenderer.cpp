#include "pch.h"
#include "SpriteRenderer.h"
#include "Texture.h"

#include "CameraSystem.h"
#include "Camera.h"

void SpriteRenderer::Initialize(const wchar_t* filePath)
{
	_texture = g_pResourceMgr->LoadResource<Texture>(filePath);
}

void SpriteRenderer::Render(ID3D11DeviceContext* pDeviceContext)
{
	if (!_description.activeDraw) return;

	if (GE::SpriteDescription::D2D != _description.type)
	{
		Camera* pCamera = g_pCameraSystem->GetCurrentCamera();
		CameraData data
		{
			.view = pCamera->GetViewMatrix().Transpose(),
			.projection = pCamera->GetProjectionMatrix().Transpose(),
			.cameraPosition = pCamera->GetPosition()
		};

		g_pConstantBuffer->UpdateConstantBuffer(L"CameraData", &data);
	}

	auto* pSRV = _texture->Get();
	pDeviceContext->PSSetShaderResources(0, 1, &pSRV);
	g_pSprite->Render(_description.type);
}

void SpriteRenderer::Release()
{
	delete this;
}

void SpriteRenderer::GetDesc(GE::SpriteDescription* out)
{
	(*out) = _description;
}

void SpriteRenderer::SetDesc(const GE::SpriteDescription* in)
{
	_description = (*in);
}