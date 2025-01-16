#include "pch.h"
#include "Bloom.h"
#include "PixelShader.h"

Bloom::Bloom()
{
	_psBloomCurve = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/BloomCurvePS.cso");
	_psSampling = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/SamplingPS.cso");

	_desc =
	{
		.mask = 0.3f,
		.threshold = 1.f
	};
}

void Bloom::InitializeOnce()
{
	g_pViewManagement->AddRenderTargetView(L"Bloom", Vector2(g_width, g_height));

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

void Bloom::Render(ID3D11ShaderResourceView* pSourceSRV)
{
	//float downScale = 1.f;
	//unsigned int numViewports = 0;
	//D3D11_VIEWPORT* oldViewPorts = nullptr;
	//_pDeviceContext->RSGetViewports(&numViewports, oldViewPorts);
	//
	//// BloomCurve
	//auto* pRTV = g_pViewManagement->GetRenderTargetView(L"Bloom");
	//auto* pSRV = g_pViewManagement->GetShaderResourceView(L"Bloom");

	//_pDeviceContext->OMSetRenderTargets(1, &pRTV, nullptr);
	//_pDeviceContext->ClearRenderTargetView(pRTV, COLOR_ZERO);
	//_pDeviceContext->PSSetShaderResources(0, 1, &pSourceSRV);
	//_psBloomCurve->SetPixelShader();
	//g_pQuad->Render();


	//auto& [RTVs, SRVs] = g_pViewManagement->GetRenderTargetGroup(L"DownScale");
	//size_t count = RTVs.size();

	//// DownScale
	//for (size_t i = 0; i < count; i++)
	//{
	//	downScale *= 0.5f;
	//	Sampling(g_width * downScale, g_height * downScale, RTVs[i]);
	//	_pDeviceContext->PSSetShaderResources(0, 1, &SRVs[i]);
	//}

	//// UpScale
	//for (size_t i = count - 1; i >= 0; i--)
	//{
	//	Sampling(g_width * downScale, g_height * downScale, RTVs[i]);
	//	_pDeviceContext->PSSetShaderResources(0, 1, &SRVs[i]);
	//	downScale *= 2.f;
	//}

	//_pDeviceContext->RSSetViewports(numViewports, oldViewPorts);
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

	_psSampling->SetPixelShader();
	g_pQuad->Render();

	ID3D11RenderTargetView* nullSRV{ nullptr };
	_pDeviceContext->OMSetRenderTargets(1, &nullSRV, nullptr);
}