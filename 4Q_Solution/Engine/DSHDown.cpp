#include "pch.h"
#include "DSHDown.h"

Engine::DSHInput::Trigger::Down::Down() :
	_down(nullptr)
{
}

void Engine::DSHInput::Trigger::Down::Setup(DSH::Input::Trigger::IDown* down)
{
	down->AddRef();
	_down = down;
}

void Engine::DSHInput::Trigger::Down::Finalize()
{
	Utility::SafeRelease()(&_down);
}

void Engine::DSHInput::Trigger::Down::SetComponent(Input::Component::Component* component)
{
}

void Engine::DSHInput::Trigger::Down::SetModifier(Input::Modifier::Modifier* modifier)
{
}
