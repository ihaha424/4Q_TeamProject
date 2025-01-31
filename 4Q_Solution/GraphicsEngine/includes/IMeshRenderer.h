#pragma once
#include "IBash.h"

namespace GE
{
	struct MeshDescription
	{
		unsigned int postEffectFlag;
		bool activeShadow;
		bool activeDraw;
	};

	class IMeshRenderer : public IBase
	{
	protected:
		explicit IMeshRenderer() = default;
		virtual ~IMeshRenderer() = default;
		IMeshRenderer(const IMeshRenderer&) = delete;
		IMeshRenderer(IMeshRenderer&&) = delete;
		IMeshRenderer& operator=(const IMeshRenderer&) = delete;
		IMeshRenderer& operator=(IMeshRenderer&&) = delete;

	public:
		virtual void GetDesc(MeshDescription* out) = 0;
		virtual void SetDesc(const MeshDescription* in) = 0;
	};
}