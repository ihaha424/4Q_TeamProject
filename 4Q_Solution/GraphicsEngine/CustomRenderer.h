#pragma once
#include "includes/ICustomRenderer.h"

class VertexShader;
class PixelShader;
class CustomRenderer : public GE::ICustomRenderer
{
public:
	// ICustomRenderer을(를) 통해 상속됨
	void Release() override;
	void SetPixelShader(const wchar_t* shaderFilePath) override;
	void SetVertexShader(const wchar_t* shaderFilePath) override;

private:
	std::shared_ptr<VertexShader> _vs;
	std::shared_ptr<PixelShader> _ps;
};