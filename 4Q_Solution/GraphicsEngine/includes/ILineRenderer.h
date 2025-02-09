#pragma once
#include "IBash.h"

namespace GE
{
	class ILineRenderer : public IBase
	{
	protected:
		explicit ILineRenderer() = default;
		virtual ~ILineRenderer() = default;
		ILineRenderer(const ILineRenderer&) = delete;
		ILineRenderer(ILineRenderer&&) = delete;
		ILineRenderer& operator=(const ILineRenderer&) = delete;
		ILineRenderer& operator=(ILineRenderer&&) = delete;

	public:
		virtual void SetSourcePosition(float* pArray) = 0;
		virtual void SetDestinationPosition(float* pArray) = 0;
		virtual void SetSegment(unsigned int segment) = 0;
	};
}