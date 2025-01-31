#include "pch.h"
#include "Bloom.h"
#include "PixelShader.h"

Bloom::Bloom()
{
	_psBloomCurve = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/BloomCurvePS.cso");
	_psDownSampling = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/SamplingPS.cso");
	_psUpSampling = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/SamplingPS_Up.cso");

	_desc =
	{
		.mask = 0.3f,
		.threshold = 1.f
	};
}

void Bloom::Initialize()
{
	float downScale = 0.5f;
	g_pViewManagement->AddRenderTargetView(L"DownScale1/4", Vector2(g_width * downScale, g_height * downScale));
	
	downScale *= 0.5f;
	g_pViewManagement->AddRenderTargetView(L"DownScale1/8", Vector2(g_width * downScale, g_height * downScale));

	downScale *= 0.5f;
	g_pViewManagement->AddRenderTargetView(L"DownScale1/16", Vector2(g_width * downScale, g_height * downScale));

	downScale *= 0.5f;
	g_pViewManagement->AddRenderTargetView(L"DownScale1/32", Vector2(g_width * downScale, g_height * downScale));

	downScale *= 0.5f;
	g_pViewManagement->AddRenderTargetView(L"DownScale1/64", Vector2(g_width * downScale, g_height * downScale));

	g_pViewManagement->AddRenderTargetGroup(L"DownScale", L"DownScale1/4");
	g_pViewManagement->AddRenderTargetGroup(L"DownScale", L"DownScale1/8");
	g_pViewManagement->AddRenderTargetGroup(L"DownScale", L"DownScale1/16");
	g_pViewManagement->AddRenderTargetGroup(L"DownScale", L"DownScale1/32");
	g_pViewManagement->AddRenderTargetGroup(L"DownScale", L"DownScale1/64");
}

void Bloom::Release()
{
	delete this;
}

void Bloom::GetDesc(GE::BlOOM_DESC* pOutDesc)
{
	(*pOutDesc) = _desc;
}

void Bloom::SetDesc(GE::BlOOM_DESC* pInDesc)
{
	_desc = (*pInDesc);
}

void Bloom::Render()
{
	float downScale = 1.f;
	
	// BloomCurve
	auto* pRTV = g_pViewManagement->GetRenderTargetView(L"PostProcess");
	auto* pSRV = g_pViewManagement->GetShaderResourceView(L"PostProcess");

	_pDeviceContext->OMSetRenderTargets(1, &pRTV, nullptr);
	_pDeviceContext->ClearRenderTargetView(pRTV, COLOR_ZERO);
	_psBloomCurve->SetPixelShader();
	g_pQuad->Render();

	_pDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
	_pDeviceContext->PSSetShaderResources(2, 1, &pSRV);

	auto& [RTVs, SRVs] = g_pViewManagement->GetRenderTargetGroup(L"DownScale");
	int count = (int)RTVs.size();

	// DownScale
	for (int i = 0; i < count; i++)
	{
		downScale *= 0.5f;
		Sampling(g_width * downScale, g_height * downScale, RTVs[i]);
		_pDeviceContext->PSSetShaderResources(2, 1, &SRVs[i]);
	}

	/*ID3D11ShaderResourceView* nullSRV = nullptr;
	_pDeviceContext->PSSetShaderResources(0, 1, &nullSRV);*/

	// UpScale
	D3D11_VIEWPORT viewport
	{
		.Width = g_width,
		.Height = g_height,
		.MaxDepth = 1.f
	};

	_pDeviceContext->RSSetViewports(1, &viewport);

	_pDeviceContext->OMSetRenderTargets(1, &pRTV, nullptr);
	_pDeviceContext->PSSetShaderResources(2, (unsigned int)SRVs.size(), SRVs.data());
	_psUpSampling->SetPixelShader();
	g_pQuad->Render();
}

void Bloom::Sampling(float width, float height, ID3D11RenderTargetView* pRTV)
{
	D3D11_VIEWPORT viewport
	{
		.Width = width,
		.Height = height,
		.MaxDepth = 1.f
	};

	_pDeviceContext->RSSetViewports(1, &viewport);
	_pDeviceContext->OMSetRenderTargets(1, &pRTV, nullptr);

	_psDownSampling->SetPixelShader();
	g_pQuad->Render();

	_pDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
}