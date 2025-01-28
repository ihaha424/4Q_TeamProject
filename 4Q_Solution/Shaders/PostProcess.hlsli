#ifndef __PostProcess__
#define __PostProcess__

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 uv : TEXCOORD0;
};

Texture2D txSource    : register(t0);
Texture2D<uint> txLayerMask : register(t1);

SamplerState samLinear_wrap : register(s0);

cbuffer LayerMask : register(b0)
{
    uint layerMask;
}

inline float LayerMasking(float2 uv)
{
    uint mask = txLayerMask.Load(int3(uv * float2(1920, 1080), 0));
    return min((layerMask & mask), 1);
}

#endif