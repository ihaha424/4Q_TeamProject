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

		DSH::Input::Modifier::INegative* Get() const;

	private:
		DSH::Input::Modifier::INegative* _negative;
	};
}
