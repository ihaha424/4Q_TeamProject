#pragma once
#include "IRenderer.h"
#include "Light.h"

class Texture;
class VertexShader;
class PixelShader;
class Mesh;
class SkyBoxRenderer;
class DX11Renderer : public IRenderer
{
	using DrawData = std::pair<unsigned int, Mesh*>;
	enum TextureType { Diffuse, Normal, Specular, Emissive, ShadowPosition, End };
public:
	explicit DX11Renderer() = default;
	virtual ~DX11Renderer() = default;

public:
	void Initialize() override;
	void Render() override;

private:
	void SetViewport(float width, float height);

	void ShadowPass();
	void DeferredPass(std::list<DrawData>& renderData, ID3D11RenderTargetView* pRTV);
	void ForwardPass(std::list<DrawData>& renderData, ID3D11RenderTargetView* pRTV);
	void SkyBoxPass(std::list<SkyBoxRenderer*>& skyBoxes);
	void PostProcessing();
	void BlendPass();
	void RenderMesh(std::list<DrawData>& renderData, std::shared_ptr<PixelShader>& pixelShader);

private:
	void InitState();
	void InitOptional();
	void InitMRT();
	void InitShader();
	void InitDepthStencil();
	void InitStructuredBuffer();

private:
	// IRenderer을(를) 통해 상속됨
	void Free() override;

private:
	std::vector<Matrix>					_matrices;
	std::vector<Matrix>					_boneMatrices;
	std::vector<LightData>				_directionalLights;
	std::vector<LightData>				_pointLights;
	D3D11_VIEWPORT						_viewport{};

	// Shaders
	std::shared_ptr<VertexShader>		_vsShadow[MeshType::End];
	std::shared_ptr<PixelShader>		_psDeferred;
	std::shared_ptr<PixelShader>		_psBlend;
	std::shared_ptr<PixelShader>		_psGBuffer;
	std::shared_ptr<PixelShader>		_psLighting;

	// Device
	ID3D11DeviceContext*				_pDeviceContext{ nullptr };

	// View
	ID3D11DepthStencilView*				_pDefaultDSV{ nullptr };
	ID3D11ShaderResourceView*			_pDefaultSRV{ nullptr };
	ID3D11DepthStencilView*				_pShadowDSV{ nullptr };
	ID3D11ShaderResourceView*			_pShadowSRV{ nullptr };

	// State
	ID3D11BlendState*					_pBlendState{ nullptr };
	ID3D11RasterizerState*				_pRSSkyBoxState{ nullptr };

	// Layer
	std::vector<ID3D11ShaderResourceView*> _layerSRVs;
};