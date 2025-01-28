#ifndef __ToneMapping__
#define __ToneMapping__

#include "PostProcess.hlsli"
#include "ShaderUtilities.hlsli"

static const float A = 0.15;
static const float B = 0.50;
static const float C = 0.10;
static const float D = 0.20;
static const float E = 0.02;
static const float F = 0.30;
static const float W = 11.2;

float3 Uncharted2Tonemap(float3 x)
{
    return ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;
}

Texture2D txPostProcess : register(t2);

float4 main(PS_INPUT input) : SV_Target
{
    float4 source0 = txSource.Sample(samLinear_wrap, input.uv);
    float4 source1 = txPostProcess.Sample(samLinear_wrap, input.uv);
    
    float3 blend = (source0 + source1).rgb;
    
    float3 texColor = GammaToLinearSpace(blend);
    texColor *= 16; // Hardcoded Exposure Adjustment

    float ExposureBias = 2.0f;
    float3 curr = Uncharted2Tonemap(ExposureBias * texColor);

    float3 whiteScale = 1.0f / Uncharted2Tonemap(W);
    float3 color = curr * whiteScale;
      
    float3 retColor = LinearToGammaSpace(color);
    return float4(retColor, 1);
}

#endif