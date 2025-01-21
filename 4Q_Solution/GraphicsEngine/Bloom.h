#pragma once
#include "Filter.h"
#include "includes/IBloom.h"

class PixelShader;
class Bloom : public Filter, public GE::IBloom
{
public:
	explicit Bloom();
	virtual ~Bloom() = default;

public:
	void InitializeOnce() override;

public:
	// IGaussianBlur을(를) 통해 상속됨
	void Release() override;
	void GetDesc(GE::BlOOM_DESC* pOutDesc) override;
	void SetDesc(GE::BlOOM_DESC* pInDesc) override;

public:
	// PostProcess을(를) 통해 상속됨
	void Render(ID3D11ShaderResourceView* pSourceSRV) override;

private:
	void Sampling(float width, float height, ID3D11RenderTargetView* pRTV);

private:
	std::shared_ptr<PixelShader> _psBloomCurve;
	std::shared_ptr<PixelShader> _psSampling;
	GE::BlOOM_DESC _desc;
};