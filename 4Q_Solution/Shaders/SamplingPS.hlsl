#include "PostProcess.hlsli"

#ifdef Up
Texture2D txSource1 : register(t2);
Texture2D txSource2 : register(t3);
Texture2D txSource3 : register(t4);
Texture2D txSource4 : register(t5);
#else
Texture2D txSource1 : register(t2);
#endif


float4 main(PS_INPUT input) : SV_Target
{
    float4 color = 0;    
    uint mask = txLayerMask.Sample(samLinear_wrap, input.uv).r;
    
#ifdef Up
    color += txSource1.Sample(samLinear_wrap, input.uv);
    color += txSource2.Sample(samLinear_wrap, input.uv);
    color += txSource3.Sample(samLinear_wrap, input.uv);
    color += txSource4.Sample(samLinear_wrap, input.uv);
#else
    color = txSource1.Sample(samLinear_wrap, input.uv);
#endif
    
    return color * LayerMasking(input.uv);
}