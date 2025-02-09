struct VS_INPUT
{
    float3 position : POSITION;
    float2 uv       : TEXCOORD;
};

[maxvertexcount(4)]
void GS_main(line VS_INPUT input[2], inout TriangleStream<VS_INPUT> outputStream)
{
    VS_INPUT v0, v1, v2, v3;

    float3 p0 = input[0].position;
    float3 p1 = input[1].position;

    // 선의 방향 벡터 (p0 -> p1)
    float2 dir = normalize(p1.xy - p0.xy);
    
    // 두께를 위한 수직 벡터 (dir과 수직)
    float2 perp = float2(-dir.y, dir.x) * 0.05f; // 두께 설정

    // Quad 정점 생성
    v0.position = float4(p0.xy + perp, p0.z, 1.0f);
    v1.position = float4(p1.xy + perp, p1.z, 1.0f);
    v2.position = float4(p0.xy - perp, p0.z, 1.0f);
    v3.position = float4(p1.xy - perp, p1.z, 1.0f);

    // UV 좌표 (텍스처 적용 가능)
    v0.uv = float2(0, 0);
    v1.uv = float2(1, 0);
    v2.uv = float2(0, 1);
    v3.uv = float2(1, 1);

    // 삼각형 2개로 Quad 생성
    outputStream.Append(v0);
    outputStream.Append(v1);
    outputStream.Append(v2);
    outputStream.RestartStrip();
    
    outputStream.Append(v2);
    outputStream.Append(v1);
    outputStream.Append(v3);
    outputStream.RestartStrip();
}