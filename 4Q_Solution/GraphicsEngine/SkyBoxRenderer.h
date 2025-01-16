#pragma once
#include "MeshRenderer.h"
#include "includes/ISkyBoxRenderer.h"

class Texture;
class PixelShader;
class SkyBoxRenderer : public MeshRenderer, public GE::ISkyBoxRenderer
{
	enum Type { Diffsue, Specular, BRDF, End };
public:
	explicit SkyBoxRenderer() = default;
	virtual ~SkyBoxRenderer() = default;

public:
	// ISkyBoxRenderer을(를) 통해 상속됨
	void SetSkyBoxTexture(const wchar_t* filePath) override;
	void SetBRDFTexture(const wchar_t* filePath) override;
	void SetDiffuseTexture(const wchar_t* filePath) override;
	void SetSpecularTexture(const wchar_t* filePath) override;
	void SetIBLTextures(ID3D11DeviceContext* pDeviceContext);

public:
	// MeshRenderer을(를) 통해 상속됨
	void Initialize(const wchar_t* filePath) override;
	void Render(ID3D11DeviceContext* pDeviceContext);

private:
	std::shared_ptr<Texture> _textures[End];
	std::shared_ptr<Texture> _skyBox;
	std::shared_ptr<PixelShader> _pixelShader;
};