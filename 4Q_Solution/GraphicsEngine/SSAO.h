#pragma once
#include "Filter.h"

class SSAO : public Filter
{
public:
	explicit SSAO() = default;
	virtual ~SSAO() = default;

public:
	// Filter을(를) 통해 상속됨
	void Initialize() override;
	void Render() override;

private:
	std::vector<Vector3> _kernel;
	std::shared_ptr<PixelShader> _psSSAO;
};