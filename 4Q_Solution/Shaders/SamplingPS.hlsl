#include "PostProcess.hlsli"

Texture2D txSource1 : register(t2);


float4 main(PS_INPUT input) : SV_Target
{
    float4 color = 0;    
    uint mask = txLayerMask.Sample(samLinear_wrap, input.uv).r;
    
    color += txSource1.SampleLevel(samLinear_wrap, input.uv, 1);
    color += txSource1.SampleLevel(samLinear_wrap, input.uv, 2);
    color += txSource1.SampleLevel(samLinear_wrap, input.uv, 3);
    color += txSource1.SampleLevel(samLinear_wrap, input.uv, 4);
    color += txSource1.SampleLevel(samLinear_wrap, input.uv, 5);
    
    return float4(color.rgb, 1.f) * LayerMasking(input.uv);
}