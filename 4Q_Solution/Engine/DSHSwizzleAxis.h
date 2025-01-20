#pragma once
#include "SwizzleAxis.h"

namespace Engine::DSHInput::Modifier
{
	class SwizzleAxis final : public Input::Modifier::SwizzleAxis
	{
	public:
		SwizzleAxis();

		void Setup(DSH::Input::Modifier::ISwizzleAxis* swizzleAxis);

		void SetType(Type type) override;

	private:
		DSH::Input::Modifier::ISwizzleAxis* _swizzleAxis;

		std::unordered_map<Type, DSH::Input::Modifier::ISwizzleAxis::Type> _typeMap;
	};
}
