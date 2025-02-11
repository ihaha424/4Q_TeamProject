struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 uv       : TEXCOORD;
};

cbuffer WaveData
{
    float waveTime;
    float waveAmplitude;
    float waveFrequency;
}

Texture2D txBase        : register(t0);
Texture2D txMask        : register(t1);
Texture2D txGradient    : register(t2);

SamplerState samLinear_wrap : register(s0);
SamplerState samLinear_clamp : register(s1);

float random(float2 uv)
{
    return frac(sin(dot(uv.xy, float2(12.9898, 78.233))) * 43758.5453);
}

float4 main(PS_INPUT input) : SV_Target
{
    float base = txBase.Sample(samLinear_wrap, input.uv + float2(waveTime, 0)).r;
    float mask = txMask.Sample(samLinear_wrap, input.uv).r;
    float noise = random(input.uv * waveTime * 10.0);
    
    float3 baseColor = txGradient.Sample(samLinear_wrap, input.uv).rgb;
    float4 color = float4(baseColor * base + baseColor, 1);
    color.a = mask;
    
    return color;
}