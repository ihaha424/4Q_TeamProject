#include "pch.h"
#include "SSAO.h"
#include "PixelShader.h"
#include "Texture.h"

#include <random>
const unsigned int KENEL_SIZE = 32;

float RandomFloat(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(gen);
}

ID3D11ShaderResourceView* SSAO::GetTexture()
{
    return nullptr;
}

void SSAO::Initialize()
{
    _kernel.reserve(KENEL_SIZE);
    for (unsigned int i = 0; i < KENEL_SIZE; ++i)
    {
        Vector3 sample(RandomFloat(-1.f, 1.f), RandomFloat(-1.f, 1.f), RandomFloat( 0.f, 1.f));

        sample.Normalize();
        sample *= RandomFloat(0.0f, 1.0f);
        float scale = float(i) / KENEL_SIZE;
        scale = std::lerp(0.1f, 1.f, scale * scale);
        sample *= scale;
        _kernel.emplace_back(sample);
    }

    _texture = g_pResourceMgr->LoadResource<Texture>(L"../Resources/Textures/AO_Noise.png");
    _psSSAO[Sample] = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/SSAOPS_Sampling.cso");
    _psSSAO[Blend] = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/SSAOPS_Blend.cso");
    _psGaussianBlur[X] = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/GaussianBlurPS_X.cso");
    _psGaussianBlur[Y] = g_pResourceMgr->LoadResource<PixelShader>(L"../Resources/Shaders/GaussianBlurPS_Y.cso");
}

void SSAO::Render()
{
    auto* pDSSRV = g_pViewManagement->GetShaderResourceView(L"DefaultDepth");
    auto* pNormalSRV = g_pViewManagement->GetShaderResourceView(L"Normal");
    auto* noise = _texture->Get();

    // SSAO ÃßÃâ
    _pDeviceContext->OMSetRenderTargets(1, &_pPostRTV, nullptr);
    _pDeviceContext->ClearRenderTargetView(_pPostRTV, COLOR_ZERO);
    _pDeviceContext->PSSetShaderResources(2, 1, &pDSSRV);
    _pDeviceContext->PSSetShaderResources(3, 1, &pNormalSRV);
    _pDeviceContext->PSSetShaderResources(4, 1, &noise);

    _psSSAO[Sample]->SetPixelShader();
    g_pQuad->Render();

    // X Blur
    _pDeviceContext->OMSetRenderTargets(1, &_pBlendRTVs[0], nullptr);
    _pDeviceContext->PSSetShaderResources(2, 1, &_pPostSRV);
    _psGaussianBlur[X]->SetPixelShader();
    g_pQuad->Render();
    ClearBindResource(_pDeviceContext, 2, 1);

    // Y Blur
    _pDeviceContext->OMSetRenderTargets(1, &_pBlendRTVs[1], nullptr);
    _pDeviceContext->PSSetShaderResources(2, 1, &_pBlendSRVs[0]);
    _psGaussianBlur[Y]->SetPixelShader();
    g_pQuad->Render();
    ClearBindResource(_pDeviceContext, 2, 1);

    // AO Blend
    auto* pAmbientSRV = g_pViewManagement->GetShaderResourceView(L"Ambient");

    _pDeviceContext->OMSetRenderTargets(1, &_pPostRTV, nullptr);
    _pDeviceContext->PSSetShaderResources(2, 1, &_pBlendSRVs[1]);
    _pDeviceContext->PSSetShaderResources(3, 1, &pAmbientSRV);
    _psSSAO[Blend]->SetPixelShader();
    g_pQuad->Render();

    _pDeviceContext->OMSetRenderTargets(0, nullptr, nullptr);
    ClearBindResource(_pDeviceContext, 2, 3);
}

void SSAO::Free()
{
}
