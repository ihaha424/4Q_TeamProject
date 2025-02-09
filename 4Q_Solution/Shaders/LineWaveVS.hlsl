struct VS_INPUT
{
    float3 position : POSITION;
    float2 uv       : TEXCOORD0;
    float2 waveData : TEXCOORD1;
};

struct VS_OUTPUT
{
    float4 position : SV_POSITION;
    float2 uv       : TEXCOORD;
};

cbuffer WaveData
{
    float time;
    float waveAmplitude;
    float waveFrequency;
}

cbuffer ViewProjection
{
    matrix vp;
    matrix shadowVP;
}

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output = (VS_OUTPUT) 0;

    float t = input.waveData.x;
    float direction = input.waveData.y;

    // 흔들리는 효과 적용
    float waveOffset = sin(time * waveFrequency + t * 10.0) * waveAmplitude * direction;
    
    // Y축 방향으로 흔들리게 적용
    float3 newPosition = input.position;
    newPosition.y += waveOffset;

    output.position = mul(float4(newPosition, 1.0f), vp);
    output.uv = input.uv;
    
    return output;
}