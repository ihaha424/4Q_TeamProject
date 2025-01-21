Texture2D txSource : register(t0);

SamplerState samLinear_wrap : register(s0);

float4 main(float2 uv : TEXCOORD0) : SV_Target
{        
    return float4(txSource.Sample(samLinear_wrap, uv).rgb, 1);
}