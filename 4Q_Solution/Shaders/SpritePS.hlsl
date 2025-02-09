struct PS_INPUT
{
    float4 position      : SV_POSITION;
    float2 uv            : TEXCOORD0;
};

Texture2D txSprite           : register(t0);
SamplerState samLinear_wrap  : register(s0);

float4 main(PS_INPUT input) : SV_Target
{        
    return txSprite.Sample(samLinear_wrap, input.uv);
}