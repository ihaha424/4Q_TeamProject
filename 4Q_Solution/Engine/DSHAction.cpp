#include "pch.h"
#include "DSHAction.h"

Engine::DSHInput::Action::Action():
	_action(nullptr)
{
}

Engine::DSHInput::Action::~Action()
{
	Utility::SafeRelease()(&_action);
}

void Engine::DSHInput::Action::Setup(DSH::Input::IAction* action)
{
	action->AddRef();
	_action = action;
}
