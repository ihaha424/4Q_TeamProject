#pragma once
#include "Action.h"

namespace Engine::DSHInput
{
	class Action final : public Input::Action
	{
	public:
		Action();
		~Action() override;

		void Setup(DSH::Input::IAction* action);

	private:
		DSH::Input::IAction* _action;
	};
}