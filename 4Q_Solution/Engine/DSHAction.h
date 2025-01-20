#pragma once
#include "Action.h"

namespace Engine::DSHInput
{
	class Action final : public Input::Action
	{
	public:
		Action();

		void Setup(DSH::Input::IAction* action);

		void Finalize() override;
		
		void GetTrigger(Input::Trigger::IDown** trigger) override;

	private:
		DSH::Input::IAction* _action;

		std::vector<Input::Trigger::Trigger*> _triggers;
	};
}