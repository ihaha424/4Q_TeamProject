#include "pch.h"
#include "Blur.h"

void Blur::Release()
{
	delete this;
}

void Blur::GetDesc(GE::BLUR_DESC* pOutDesc)
{
}

void Blur::SetDesc(GE::BLUR_DESC* pInDesc)
{
}

void Blur::Initialize()
{
}

void Blur::Render(ID3D11ShaderResourceView* pSourceSRV)
{
	auto* pRTV = g_pViewManagement->GetRenderTargetView(L"PostProcess");
	auto* pSRV = g_pViewManagement->GetShaderResourceView(L"PostProcess");
	_pDeviceContext->ClearRenderTargetView(pRTV, COLOR_ZERO);
}
