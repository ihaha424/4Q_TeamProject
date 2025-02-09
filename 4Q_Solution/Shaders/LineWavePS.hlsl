struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 uv       : TEXCOORD;
};

Texture2D txBase : register(t0);
Texture2D txMask : register(t1);

SamplerState samLinear_wrap : register(s0);

float4 main(PS_INPUT input) : SV_Target
{
    float3 base = txBase.Sample(samLinear_wrap, input.uv).rgb;
    float  mask = txMask.Sample(samLinear_wrap, input.uv).r;
    
    return float4(base * mask, 1);
}