#pragma once

enum class ShaderType { Vertex, Pixel };
enum class TextureType { Diffuse, Normal, Specular, Emission, Opacity, LightMap, Metalness, Roughness, End };

namespace MeshType
{
	enum Type { Static, Skeletal, SkyBox, End };
}

namespace RenderType
{
	enum Type { NoneAlpha, Alpha, End };
}

constexpr float SHADOW_WIDTH = 8192.f;
constexpr float SHADOW_HEIGHT = 8192.f;
constexpr unsigned int MAX_BONE_MATRIX = 128;
constexpr unsigned int MAX_DRAW_OBJECT = 1024;
constexpr float COLOR_ZERO[4]{ 0.f, 0.f, 0.f, 1.f };