#ifndef __PostProcess__
#define __PostProcess__

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
};

Texture2D txSource : register(t0);

SamplerState samLinear_wrap : register(s0);

cbuffer LayerMask : register(b0)
{
    uint layerMask;
}

#endif