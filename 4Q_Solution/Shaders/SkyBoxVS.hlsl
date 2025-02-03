struct PS_INPUT
{
    float4 position      : SV_POSITION;
    float3 worldPosition : POSITION;
};

cbuffer ViewProjection : register(b0)
{
    matrix vp;
    matrix shadowVP;
}

PS_INPUT main(float4 position : POSITION)
{
    PS_INPUT output = (PS_INPUT) 0;
    
    //matrix skyVP = vp;
    //skyVP._13_23_33 = 0;
    
    output.worldPosition = position.xyz;
    output.position = mul(position, vp);
    
    return output;
}