#pragma once
#include "IBash.h"

namespace GE
{
	class IAnimator : public IBase
	{
	protected:
		explicit IAnimator() = default;
		virtual ~IAnimator() = default;
		IAnimator(const IAnimator&) = delete;
		IAnimator(IAnimator&&) = delete;
		IAnimator& operator=(const IAnimator&) = delete;
		IAnimator& operator=(IAnimator&&) = delete;

	public:
		virtual void ChangeAnimation(const char* name) = 0;
		virtual bool IsLastFrame(float interval) const = 0;
	};
}