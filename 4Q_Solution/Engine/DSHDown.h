#pragma once
#include "Down.h"

namespace Engine::DSHInput::Trigger
{
	class Down final : public Input::Trigger::Down
	{
	public:
		Down();

		void Setup(DSH::Input::Trigger::IDown* down);

		void Finalize() override;

		void SetComponent(Input::Component::Component* component) override;
		void SetModifier(Input::Modifier::Modifier* modifier) override;

	private:
		DSH::Input::Trigger::IDown* _down;
	};
}