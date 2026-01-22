#include "pch.h"
#include "DSHAction.h"
#include "DSHDown.h"

std::unordered_map<Engine::Input::Trigger::Event, DSH::Input::Trigger::Event> Engine::DSHInput::Action::_eventMap
{
	std::make_pair(Input::Trigger::Event::Completed, DSH::Input::Trigger::Event::Completed),
	std::make_pair(Input::Trigger::Event::Started, DSH::Input::Trigger::Event::Started),
	std::make_pair(Input::Trigger::Event::Ongoing, DSH::Input::Trigger::Event::Ongoing),
	std::make_pair(Input::Trigger::Event::Canceled, DSH::Input::Trigger::Event::Canceled),
	std::make_pair(Input::Trigger::Event::Triggered, DSH::Input::Trigger::Event::Triggered)
};

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
	std::ranges::for_each(_triggers, Utility::SafeDelete());
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

void Engine::DSHInput::Action::AddListener(const Input::Trigger::Event event, Listener listener)
{
	_action->AddListener(_eventMap[event], [listener](const DSH::Input::Value value)
	{
		const Input::Value eValue{ value.x, value.y, value.z };
		listener(eValue);
	});
}
