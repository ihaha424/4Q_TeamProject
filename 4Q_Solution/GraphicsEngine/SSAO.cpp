#include "pch.h"
#include "SSAO.h"
#include "PixelShader.h"

#include <random>
const unsigned int KENEL_SIZE = 16;

float RandomFloat(float min, float max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(gen);
}

void SSAO::Initialize()
{
    _kernel.reserve(KENEL_SIZE);

    for (unsigned int i = 0; i < KENEL_SIZE; ++i)
    {
        Vector3 sample(RandomFloat(-1.f, 1.f), // x
                       RandomFloat(-1.f, 1.f), // y
                       RandomFloat(-1.f, 1.f));  // z (반구형)

        sample.Normalize();
        sample *= RandomFloat(0.0f, 1.0f);
        float scale = float(i) / KENEL_SIZE;
        scale = 0.1f + scale * scale * (1.0f - 0.1f); // 가중치 조정
        sample *= scale;
        _kernel.push_back(sample);
    }
}

void SSAO::Render()
{
    float downScale = 1.f;

    // BloomCurve
    auto* pRTV = g_pViewManagement->GetRenderTargetView(L"PostProcess");
    auto* pSRV = g_pViewManagement->GetShaderResourceView(L"PostProcess");

    _pDeviceContext->OMSetRenderTargets(1, &pRTV, nullptr);
    _pDeviceContext->ClearRenderTargetView(pRTV, COLOR_ZERO);
    _psSSAO->SetPixelShader();

    g_pQuad->Render();
}
