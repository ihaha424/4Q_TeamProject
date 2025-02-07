#pragma once
#include "IBash.h"

namespace GE
{
	class ICustomRenderer : public IBase
	{
	protected:
		explicit ICustomRenderer() = default;
		virtual ~ICustomRenderer() = default;
		ICustomRenderer(const ICustomRenderer&) = delete;
		ICustomRenderer(ICustomRenderer&&) = delete;
		ICustomRenderer& operator=(const ICustomRenderer&) = delete;
		ICustomRenderer& operator=(ICustomRenderer&&) = delete;

	public:
		virtual void SetPixelShader(const wchar_t* shaderFilePath) = 0;
		virtual void SetVertexShader(const wchar_t* shaderFilePath) = 0;
	};
}