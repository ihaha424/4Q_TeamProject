#include "pch.h"
#include "DSHInputButtonComponent.h"

Engine::DSHInput::Component::ButtonComponent::ButtonComponent():
	_button(nullptr)
{
}

void Engine::DSHInput::Component::ButtonComponent::Setup(DSH::Input::Component::IButtonComponent* button)
{
	button->AddRef();
	_button = button;
}

void Engine::DSHInput::Component::ButtonComponent::Finalize()
{
	Utility::SafeRelease()(&_button);
}

DSH::Input::Component::IButtonComponent* Engine::DSHInput::Component::ButtonComponent::Get() const
{
	return _button;
}
