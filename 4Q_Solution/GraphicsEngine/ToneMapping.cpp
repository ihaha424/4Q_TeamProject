#include "pch.h"
#include "ToneMapping.h"
#include "PixelShader.h"

void ToneMapping::Initialize()
{
	_psToneMapping = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/ToneMappingPS.cso");
	_psLuminance = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/ToneMappingPS_Lum.cso");
}

void ToneMapping::Render()
{
	// Æò±Õ ¹à±â °ª °è»ê
	auto* pSRV = g_pViewManagement->GetShaderResourceView(L"PostProcess");
	auto* pMipMapRTV = g_pViewManagement->GetRenderTargetView(L"MipMap");
	auto* pMipMapSRV = g_pViewManagement->GetShaderResourceView(L"MipMap");

	_pDeviceContext->OMSetRenderTargets(1, &pMipMapRTV, nullptr);
	_pDeviceContext->ClearRenderTargetView(pMipMapRTV, COLOR_ZERO);
	_pDeviceContext->PSSetShaderResources(2, 1, &pSRV);
	_psLuminance->SetPixelShader();
	g_pQuad->Render();

	// ¹Ó¸Ê »ý¼º
	_pDeviceContext->GenerateMips(pMipMapSRV);

	// ¹à±â °ª ±â¹Ý ³ëÃâµµ ¼³Á¤
	auto* pBackBuffer = g_pGraphicDevice->GetBackBuffer();

	_pDeviceContext->OMSetRenderTargets(1, &pBackBuffer, nullptr);
	_pDeviceContext->ClearRenderTargetView(pBackBuffer, COLOR_ZERO);
	_pDeviceContext->PSSetShaderResources(0, 1, &pSRV);
	_pDeviceContext->PSSetShaderResources(2, 1, &pMipMapSRV);
	
	_psToneMapping->SetPixelShader();
	g_pQuad->Render();

	// Reset
	ID3D11ShaderResourceView* nullSRVs[2]{ nullptr, };
	_pDeviceContext->PSSetShaderResources(0, 2, nullSRVs);
}

void ToneMapping::Free()
{
}