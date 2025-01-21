#include "pch.h"
#include "DSHInputAxisComponent.h"

Engine::DSHInput::Component::AxisComponent::AxisComponent():
	_axis(nullptr)
{
}

void Engine::DSHInput::Component::AxisComponent::Setup(DSH::Input::Component::IAxisComponent* axis)
{
	axis->AddRef();
	_axis = axis;
}

void Engine::DSHInput::Component::AxisComponent::Finalize()
{
	Utility::SafeRelease()(&_axis);
}

DSH::Input::Component::IAxisComponent* Engine::DSHInput::Component::AxisComponent::Get() const
{
	return _axis;
}
