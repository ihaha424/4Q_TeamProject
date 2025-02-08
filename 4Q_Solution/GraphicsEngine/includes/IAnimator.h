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
		virtual void ChangeAnimation(const char* animation) = 0;
		virtual void ChangeAnimation(const char* animation, const unsigned int ID) = 0;
		virtual bool IsLastFrame(float interval, const unsigned int ID) const = 0;
		virtual void SetUpSplitBone(const unsigned int maxSplit) = 0;
		virtual void SplitBone(const unsigned int ID, const char* boneName) = 0;
		virtual void SetAnimationSpeed(float speed) = 0;
		virtual void MakeParent(const char* parent, const char* child) = 0;
	};
}