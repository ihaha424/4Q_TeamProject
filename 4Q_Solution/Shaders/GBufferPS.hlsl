struct PS_INPUT
{
    float4 position         : SV_POSITION;
    float3 worldPosition    : POSITION0;
    float4 shadowPosition   : POSITION1;
    float3 normal           : NORMAL;
    float3 tangent          : TANGENT;
    float3 biTangent        : BITANGENT;
    float2 uv               : TEXCOORD;
};

struct PS_OUTPUT
{
    float4 diffuse          : SV_Target0;
    float4 normal           : SV_Target1;
    float4 specular         : SV_Target2;
    float4 emissive         : SV_Target3;
    float4 shadowPosition   : SV_Target4;
};

Texture2D txDiffuse          : register(t0);
Texture2D txNormal           : register(t1);
Texture2D txSpecular         : register(t2);
Texture2D txEmissive         : register(t3);
Texture2D txOpacity          : register(t4);
Texture2D txLight            : register(t5);
Texture2D txMetalness        : register(t6);
Texture2D txRoughness        : register(t7);

SamplerState samLinear_wrap : register(s0);

PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output = (PS_OUTPUT)0;
    
    // diffuse
    output.diffuse = txDiffuse.Sample(samLinear_wrap, input.uv);
    
    // normal
    float3 normal = txNormal.Sample(samLinear_wrap, input.uv).rgb;
    float3x3 TBN = float3x3(input.tangent, input.biTangent, input.normal);
    output.normal = float4(normalize(mul(normal * 2.0f - 1.0f, TBN)), 1);
    
    // pbr
    output.specular.r = txRoughness.Sample(samLinear_wrap, input.uv).r;
    output.specular.g = txMetalness.Sample(samLinear_wrap, input.uv).r;

    if(0.001 >= output.specular.r)
        output.specular.r = 1;
    
    // emissive
    output.emissive = txEmissive.Sample(samLinear_wrap, input.uv);
    
    //// depth
    //output.depth.r = input.position.z;
    //output.depth.g = input.clipPosition.z / input.clipPosition.w;
    
    // shadow
    output.shadowPosition = input.shadowPosition;    
    
    return output;
}
