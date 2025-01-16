#pragma once
#include "IBash.h"

namespace GE
{	
	class IMeshRenderer : public IBase
	{
	protected:
		explicit IMeshRenderer() = default;
		virtual ~IMeshRenderer() = default;
		IMeshRenderer(const IMeshRenderer&) = delete;
		IMeshRenderer(IMeshRenderer&&) = delete;
		IMeshRenderer& operator=(const IMeshRenderer&) = delete;
		IMeshRenderer& operator=(IMeshRenderer&&) = delete;	
	};
}