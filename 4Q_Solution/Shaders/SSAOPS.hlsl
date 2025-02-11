#include "PostProcess.hlsli"
#include "ShaderUtilities.hlsli"

#ifdef Sampling
Texture2D txDepth   : register(t2);
Texture2D txNormal  : register(t3);
Texture2D txNoise   : register(t4);

#define SAMPLES 16
static const float3 sample_sphere[SAMPLES] =
{
    float3(0.5381, 0.1856, -0.4319), float3(0.1379, 0.2486, 0.4430),
    float3(0.3371, 0.5679, -0.0057), float3(-0.6999, -0.0451, -0.0019),
    float3(0.0689, -0.1598, -0.8547), float3(0.0560, 0.0069, -0.1843),
    float3(-0.0146, 0.1402, 0.0762), float3(0.0100, -0.1924, -0.0344),
    float3(-0.3577, -0.5301, -0.4358), float3(-0.3169, 0.1063, 0.0158),
    float3(0.0103, -0.5869, 0.0046), float3(-0.0897, -0.4940, 0.3287),
    float3(0.7119, -0.0154, -0.0918), float3(-0.0533, 0.0596, -0.5411),
    float3(0.0352, -0.0631, 0.5460), float3(-0.4776, 0.2847, -0.0271)
};

cbuffer CameraDesc
{
    matrix viewprojInv;
    float3 cameraPosition;
}

cbuffer ViewProjection
{
    matrix vp;
    matrix shadowVP;
}

float3 GetRandom(float2 uv)
{
    float2 offsetUV =  screenSize * uv / 4.0f;
    return normalize(txNoise.Sample(samLinear_wrap, offsetUV).xyz * 2.0f - 1.0f);
}

float GetViewDepth(float2 uv)
{
    return txDepth.Sample(samLinear_wrap, uv).r;
}

float3 NormalFromDepth(float depth, float2 uv)
{
    const float2 offset1 = float2(0.0, 0.001);
    const float2 offset2 = float2(0.001, 0.0);
   
    float depth1 = GetViewDepth(uv + offset1);
    float depth2 = GetViewDepth(uv + offset2);
   
    float3 p1 = float3(offset1, depth1 - depth);
    float3 p2 = float3(offset2, depth2 - depth);
   
    float3 normal = cross(p1, p2);
    normal.z = -normal.z;
   
    return normalize(normal);
}

float3 ReconstructViewPos(float2 uv)
{
    float depth = txDepth.Sample(samLinear_wrap, uv).r;
    float4 pos = mul(float4(uv * 2.0 - 1.0, depth, 1.0), viewprojInv);
    return pos.xyz / pos.w;
}

#else
Texture2D txSSAO    : register(t2);
Texture2D txAmbient : register(t3);
#endif

float4 main(PS_INPUT input) : SV_Target
{
#ifdef Sampling
    float total_strength = 4.7;
    float base = 2.3;
    float area = 0.0075;
    float falloff = 0.000001;
    float threshold = 0;
    float radius = 0.01;
    float depthWeight = 0.5;
    
    float3 random = GetRandom(input.uv);
    float depth = GetViewDepth(input.uv);
    
    float3 position = float3(input.uv, depth);
    float3 normal = txNormal.Sample(samLinear_wrap, input.uv).xyz;
    float radius_depth = radius / (depth);
    float occlusion = 0.0;
    
    [unroll]
    for (int i = 0; i < SAMPLES; i++)
    {
        float3 ray = radius_depth * reflect(sample_sphere[i], random);
        float3 hemi_ray = position + sign(dot(ray, normal)) * ray;
      
        float occ_depth = GetViewDepth(saturate(hemi_ray.xy));
        float difference = depth - occ_depth;
      
        occlusion += smoothstep(falloff, area, difference);
    }
    
    float luminance = total_strength * 2 * occlusion * (1.0 / SAMPLES);
    float ao = 1.0 - luminance;
    ao += ((ao > threshold) ? 1 : base);
    float3 Ambient = saturate(ao);
    Ambient = saturate(Ambient + depth * depthWeight);
    
    return float4(Ambient * Ambient, 1.0);
    
    //float total_strength = 4.7;
    //float base = 2.3;
    //float area = 0.0075;
    //float falloff = 0.000001;
    //float threshold = 0;
    //float radius = 0.01;
    //float depthWeight = 0.5;
    //float bias = 0.0001;
    
    //float3 pos = ReconstructViewPos(input.uv);
    //float3 N = txNormal.Sample(samLinear_wrap, input.uv).xyz;
    
    //float3 randomVec = normalize(txNoise.Sample(samLinear_wrap, input.uv * 4.0).xyz);

    //float occlusion = 0.0;
    //for (int i = 0; i < SAMPLES; i++)
    //{
    //    float3 sampleOffset = reflect(sample_sphere[i].xyz, randomVec);
    //    float3 samplePos = pos + sampleOffset * radius;
        
    //    float4 offsetPos = mul(float4(samplePos, 1.0), vp);
    //    float2 offsetUV = offsetPos.xy / offsetPos.w * 0.5 + 0.5;

    //    float sampleDepth = txDepth.Sample(samLinear_wrap, offsetUV).r;
    //    float3 sampleViewPos = ReconstructViewPos(offsetUV);
        
    //    float rangeCheck = smoothstep(0.0, 1.0, radius / abs(pos.z - sampleViewPos.z));
    //    occlusion += (sampleViewPos.z >= samplePos.z + bias ? 1.0 : 0.0) * rangeCheck;
    //}
    
    //occlusion = 1.0 - (occlusion / 64.0);
    //return float4(occlusion.xxx, 1);
#else
    float SSAO = txSSAO.Sample(samLinear_wrap, input.uv).r;
    float4 ambient = txAmbient.Sample(samLinear_wrap, input.uv);
    float4 color = float4(ambient.rgb * ambient.a * SSAO, 1);
    return color;
#endif
}