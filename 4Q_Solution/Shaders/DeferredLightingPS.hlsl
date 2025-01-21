#include "ShaderUtilities.hlsli"
#include "Lighting.hlsli"

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 uv       : TEXCOORD0;
};

//StructuredBuffer<Light> DirectionalLight : register(t100);
//StructuredBuffer<Light> PointLight : register(t101);

Texture2D txDiffuse         : register(t0);
Texture2D txNormal          : register(t1);
Texture2D txSpecular        : register(t2);
Texture2D txEmissive        : register(t3);
Texture2D txShadowPosition  : register(t4);
Texture2D txDepth           : register(t5);

float4 main(PS_INPUT input) : SV_Target
{
    float  depth = txDepth.Sample(samLinear_wrap, input.uv).r;
    float3 albedo = GammaToLinearSpace(txDiffuse.Sample(samLinear_wrap, input.uv).rgb);        
    float2 specular = txSpecular.Sample(samLinear_wrap, input.uv).rg;
    
    float4 NDC = float4(input.uv * 2.0 - 1, depth, 1.0);
    NDC.y = -NDC.y;
    float4 homogeneous = mul(NDC, viewprojInv);
    float3 worldPosition = homogeneous.xyz / homogeneous.w;
    
    float3 N = txNormal.Sample(samLinear_wrap, input.uv).xyz;
    float3 V = normalize(cameraPosition - worldPosition);
    
    float3 directLighting = 0;
    float3 ambientLighting = 0;
    float  shadowFactor = 1.0;
    
// PBR
    // PBR_Directional
    directLighting += DirectionalLightPBR(worldPosition, N, V, albedo, specular.r, specular.g);

    // PBR_Point
    directLighting += PointLightPBR(worldPosition, N, V, albedo, specular.r, specular.g);
    
// IBL
    //float3 irradiance = txIBL_Diffuse.Sample(samLinear_wrap, N).rgb;
    
    //uint specularTextureLevels = QuerySpecularTextureLevels(txIBL_Specular);
    //float3 Lr = 2.0 * NdotV * N - V;
    //float3 preFilteredColor = txIBL_Specular.SampleLevel(samLinear_wrap, Lr, roughness * specularTextureLevels).rgb;
    //float2 brdf = txIBL_BRDF.Sample(samLinear_clamp, float2(NdotV, roughness)).rg;
        
    //F = FresnelReflection(NdotV, F0);
    //kd = lerp(1.0 - F, 0, metalness);
    //float3 diffuseIBL = kd * albedo * irradiance;
    //float3 specularIBL = (F0 * brdf.x + brdf.y) * preFilteredColor;
    
    //ambientLighting = diffuseIBL + specularIBL;

//Shadow
    float4 shadowPosition = txShadowPosition.Sample(samLinear_wrap, input.uv);
    float currentShadowDepth = shadowPosition.z / shadowPosition.w;
    float2 uv = shadowPosition.xy / shadowPosition.w;
    
    uv.y = -uv.y;
    uv = uv * 0.5 + 0.5;
    
    if (uv.x >= 0 && uv.x <= 1 && uv.y >= 0 && uv.y <= 1)
    {
        shadowFactor = 0;
        float bias = 0.001;
        
        [unroll]
        for (int i = 0; i < 9; i++)
        {
            float2 sampleUV = uv + offsets[i] * texel;
            shadowFactor += txShadowDepth.SampleCmpLevelZero(samComparison, sampleUV, currentShadowDepth - bias);
        }
        
        shadowFactor = shadowFactor / 9.0;
    }
    
    float4 color = 0;
    
    color.rgb = shadowFactor * directLighting + ambientLighting;
    color.rgb = LinearToGammaSpace(color.rgb);
    color.a = 1;
    
    float4 emissive = txEmissive.Sample(samLinear_wrap, input.uv);
    color += emissive;
    
    return color;
}