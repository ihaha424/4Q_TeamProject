#include "ShaderUtilities.hlsli"

Texture2D txSource : register(t0);

SamplerState samLinear_wrap : register(s0);

float GetBloomCurve(float intensity, float threshold)
{
    float result = intensity;
    intensity *= 2;
    result = max(0, intensity - threshold);
    result *= result;
    return result * 0.5;
}

float4 main(float2 uv : TEXCOORD0) : SV_Target
{
    float3 source = GammaToLinearSpace(txSource.Sample(samLinear_wrap, uv).rgb);
    
    float intensity = dot(source, float3(0.3, 0.3, 0.3));
    float bloom_intensity = GetBloomCurve(intensity, 1);
    float3 bloom_color = source * bloom_intensity / intensity;
    
    return float4(LinearToGammaSpace(bloom_color), 1);
}