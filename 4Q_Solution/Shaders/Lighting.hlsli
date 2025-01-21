#ifndef __Lighting__
#define __Lighting__

#include "Constants.hlsli"
#include "LightData.hlsli"

inline float3 CalculatePointLightIntensity(float distance, float range, float intensity, float3 K)
{
    //if (range < distance)
    //    return 0;
    
    // float attenuation = 1.0 / (K.x + K.y * distance + K.z * distance * distance);
    // return intensity * attenuation;
    float attenuation = saturate(1.0f - (distance * distance / (range * range)));
    return intensity * attenuation * attenuation;
}

inline float NormalDistribution(float roughness, float3 N, float3 H)
{
    float alpha = roughness * roughness;
    float squareA = alpha * alpha;
    float NdotH = max(0.0, dot(N, H));
    float denom = NdotH * NdotH * (squareA - 1.0) + 1.0;
    return squareA / (PI * denom * denom);
}

inline float3 FresnelReflection(float costTheta, float3 F0)
{
    return F0 + (1.0 - F0) * pow(1.0 - costTheta, 5.0);
}

inline float GSchlickGGX(float cosTheta, float k)
{
    return cosTheta / (cosTheta * (1.0 - k) + k);
}

inline float GeometricAttenuation(float3 N, float3 L, float3 V, float roughness)
{
    float r = roughness + 1.0;
    float k = (r * r) / 8.0; // direct
    //float k = (roughness * roughness) * 0.5; // IBL
    return GSchlickGGX(max(0.0, dot(N, V)), k) * GSchlickGGX(max(0.0, dot(N, L)), k);
}

inline float3 DirectionalLightPBR(float3 worldPosition, float3 N, float3 V, float3 albedo, float roughness, float metalness)
{
    float3 directLighting = 0;
    float3 F0 = lerp(Fdielectric, albedo, metalness);
    float NdotV = max(0, dot(N, V));
    
    for (uint i = 0; i < numDirectionalLights; i++)
    {
        Light light = DirectionalLights[i];
        float3 L = -normalize(light.data);
        float3 H = normalize(V + L);
        float3 F = FresnelReflection(max(0, dot(H, V)), F0);
        float  D = NormalDistribution(max(0.01, roughness), N, H);
        float  G = GeometricAttenuation(N, L, V, roughness);
        float3 kd = lerp(1.0 - F, 0, metalness);
        float  NdotL = max(0, dot(N, L));
    
        float3 diffusePBR = albedo * kd / PI;
        float3 specularPBR = (F * D * G) / max(0.00001, 4.0 * NdotL * NdotV);
        directLighting += (diffusePBR + specularPBR) * NdotL * light.intensity;
    }
    
    return directLighting;
}

inline float3 PointLightPBR(float3 worldPosition, float3 N, float3 V, float3 albedo, float roughness, float metalness)
{
    float3 directLighting = 0;
    float3 F0 = lerp(Fdielectric, albedo, metalness);
    float NdotV = max(0, dot(N, V));
    
    for (uint i = 0; i < numDirectionalLights; i++)
    {
        Light light = PointLights[i];
        float3 distance = light.data - worldPosition;
        float len = length(distance);
        float3 L = distance / len;
        float3 H = normalize(V + L);
        float3 F = FresnelReflection(max(0, dot(H, V)), F0);
        float  D = NormalDistribution(max(0.01, roughness), N, H);
        float  G = GeometricAttenuation(N, L, V, roughness);
        float3 kd = lerp(1.0 - F, 0, metalness);
        float  NdotL = max(0, dot(N, L));
    
        float3 diffusePBR = albedo * kd / PI;
        float3 specularPBR = (F * D * G) / max(0.00001, 4.0 * NdotL * NdotV);
        directLighting += (diffusePBR + specularPBR) * NdotL * CalculatePointLightIntensity(len, light.range, light.intensity, light.attenuation);
    }
    
    return directLighting;
}

#endif