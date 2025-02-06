struct PS_INPUT
{
    float4 position      : SV_POSITION;
    float3 worldPosition : POSITION;
};

struct VS_INPUT
{
    float4 position : POSITION;
};
    
cbuffer ViewProjection : register(b0)
{
    matrix vp;
    matrix shadowVP;
}

cbuffer ModelIndex : register(b1)
{
    uint index;
}

StructuredBuffer<matrix> WorldMatrices : register(t0);

PS_INPUT main(VS_INPUT input)
{
    PS_INPUT output = (PS_INPUT) 0;
    
    matrix skyVP = vp;
    skyVP._13_23_33 = 0;
    
    output.position = mul(input.position, WorldMatrices[index]);   
    output.worldPosition = output.position.xyz;
    output.position = mul(output.position, vp);
    
    return output;
}