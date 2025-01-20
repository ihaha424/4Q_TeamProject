#include "pch.h"
#include "DSHAction.h"
#include "DSHDown.h"

Engine::DSHInput::Action::Action():
	_action(nullptr)
{
}

void Engine::DSHInput::Action::Setup(DSH::Input::IAction* action)
{
	action->AddRef();
	_action = action;
}

void Engine::DSHInput::Action::Finalize()
{
	std::ranges::for_each(_triggers, [](const Input::Trigger::Trigger* trigger) {delete trigger; });
	_triggers.clear();
	Utility::SafeRelease()(&_action);
}

void Engine::DSHInput::Action::GetTrigger(Input::Trigger::IDown** trigger)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (trigger == nullptr) thrower(E_INVALIDARG);
	DSH::Input::Trigger::IDown* temp = nullptr;
	thrower(_action->GetTrigger(&temp));
	Trigger::Down* down = new Trigger::Down();
	down->Setup(temp);
	Utility::SafeRelease()(&temp);
	_triggers.push_back(down);
	*trigger = down;
}
