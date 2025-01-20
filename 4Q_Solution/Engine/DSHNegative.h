#pragma once
#include "Negative.h"

namespace Engine::DSHInput::Modifier
{
	class Negative final : public Input::Modifier::Negative
	{
	public:
		Negative();

		void Setup(DSH::Input::Modifier::INegative* negative);

		void Finalize() override;

	private:
		DSH::Input::Modifier::INegative* _negative;
	};
}
