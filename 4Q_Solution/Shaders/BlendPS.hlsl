#include "ShaderUtilities.hlsli"

struct PS_INPUT
{
    float4 position         : SV_POSITION;
    float2 uv               : TEXCOORD;
};

Texture2D txBlend           : register(t0);

SamplerState samLinear_wrap : register(s0);

float4 main(PS_INPUT input) : SV_Target
{ 
    return txBlend.Sample(samLinear_wrap, input.uv);
}