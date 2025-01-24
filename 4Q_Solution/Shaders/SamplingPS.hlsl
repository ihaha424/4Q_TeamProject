#include "PostProcess.hlsli"

#ifdef Up
Texture2D txSource1 : register(t1);
Texture2D txSource2 : register(t2);
Texture2D txSource3 : register(t3);
Texture2D txSource4 : register(t4);
#endif

float4 main(PS_INPUT input) : SV_Target
{    
    float4 color = txSource.Sample(samLinear_wrap, input.uv);
    
#ifdef Up
    color += txSource1.Sample(samLinear_wrap, input.uv);
    color += txSource2.Sample(samLinear_wrap, input.uv);
    color += txSource3.Sample(samLinear_wrap, input.uv);
    color += txSource4.Sample(samLinear_wrap, input.uv);
#endif
    
    return color;
}