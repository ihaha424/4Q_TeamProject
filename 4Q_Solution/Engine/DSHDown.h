#pragma once
#include "Down.h"

namespace Engine::DSHInput::Trigger
{
	class Down final : public Input::Trigger::Down
	{
	public:
		Down();
		~Down() override;
		
		void Setup(DSH::Input::Trigger::IDown* down);

		void SetComponent(Input::Component::IButtonComponent* component) override;
		void SetComponent(Input::Component::IAxisComponent* component) override;

		void AddModifier(Input::Modifier::INegative* modifier) override;
		void AddModifier(Input::Modifier::ISwizzleAxis* modifier) override;

	private:
		DSH::Input::Trigger::IDown* _down;
	};
}