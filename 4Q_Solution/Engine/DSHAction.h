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

		void AddListener(Input::Trigger::Event event, Listener listener) override;

	private:
		static std::unordered_map<Input::Trigger::Event, DSH::Input::Trigger::Event> _eventMap;

		DSH::Input::IAction* _action;

		std::vector<Input::Trigger::ITrigger*> _triggers;
	};
}