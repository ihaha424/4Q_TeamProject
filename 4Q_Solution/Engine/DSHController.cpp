#include "pch.h"
#include "DSHController.h"

#include "DSHInputAxisComponent.h"
#include "DSHInputButtonComponent.h"

Engine::DSHInput::Device::Controller::Controller():
	_controller(nullptr)
{
	for (unsigned char button = 0; button < static_cast<unsigned char>(Button::Max); ++button)
	{
		_buttonMap[static_cast<Button>(button)] = static_cast<DSH::Input::Device::IController::Button>(button);
	}
	for (unsigned char trigger = 0; trigger < static_cast<unsigned char>(Trigger::Max); ++trigger)
	{
		_triggerMap[static_cast<Trigger>(trigger)] = static_cast<DSH::Input::Device::IController::Trigger>(trigger);
	}
	for (unsigned char thumb = 0; thumb < static_cast<unsigned char>(Thumb::Max); ++thumb)
	{
		_thumbMap[static_cast<Thumb>(thumb)] = static_cast<DSH::Input::Device::IController::Thumb>(thumb);
	}
}

void Engine::DSHInput::Device::Controller::Setup(DSH::Input::Device::IController* controller)
{
	controller->AddRef();
	_controller = controller;
}

void Engine::DSHInput::Device::Controller::Update()
{
	_controller->Update();
}

void Engine::DSHInput::Device::Controller::Reset()
{
	_controller->Reset();
}

void Engine::DSHInput::Device::Controller::Finalize()
{
	std::ranges::for_each(_buttons | std::views::values, Utility::SafeDelete());
	std::ranges::for_each(_triggers | std::views::values, Utility::SafeDelete());
	std::ranges::for_each(_thumbs | std::views::values, Utility::SafeDelete());
	Utility::SafeRelease()(&_controller, "Controller is still being referenced.");
}

bool Engine::DSHInput::Device::Controller::IsButtonDown(const Button button) const
{
	return IsButtonState(button, &DSH::Input::Component::IButtonComponent::IsDown);
}

bool Engine::DSHInput::Device::Controller::IsButtonUp(const Button button) const
{
	return IsButtonState(button, &DSH::Input::Component::IButtonComponent::IsUp);
}

bool Engine::DSHInput::Device::Controller::IsButtonPressed(const Button button) const
{
	return IsButtonState(button, &DSH::Input::Component::IButtonComponent::IsPressed);
}

bool Engine::DSHInput::Device::Controller::IsButtonReleased(const Button button) const
{
	return IsButtonState(button, &DSH::Input::Component::IButtonComponent::IsReleased);
}

void Engine::DSHInput::Device::Controller::GetComponent(const Button button, Input::Component::IButtonComponent** component)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (component == nullptr) thrower(E_INVALIDARG);
	else
	{
		if (_buttons.contains(button) == false)
		{
			Component::ButtonComponent* newComponent = new Component::ButtonComponent();
			DSH::Input::Component::IButtonComponent* dshComponent = nullptr;
			thrower(_controller->GetComponent(_buttonMap.at(button), &dshComponent));
			newComponent->Setup(dshComponent);
			_buttons[button] = newComponent;
		}
		*component = _buttons.at(button);
	}
}

void Engine::DSHInput::Device::Controller::GetComponent(const Trigger trigger, Input::Component::IAxisComponent** component)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (component == nullptr) thrower(E_INVALIDARG);
	else
	{
		if (_triggers.contains(trigger) == false)
		{
			Component::AxisComponent* newComponent = new Component::AxisComponent();
			DSH::Input::Component::IAxisComponent* dshComponent = nullptr;
			thrower(_controller->GetComponent(_triggerMap.at(trigger), &dshComponent));
			newComponent->Setup(dshComponent);
			_triggers[trigger] = newComponent;
		}
		*component = _triggers.at(trigger);
	}
}

void Engine::DSHInput::Device::Controller::GetComponent(const Thumb thumb, Input::Component::IAxisComponent** component)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (component == nullptr) thrower(E_INVALIDARG);
	else
	{
		if (_thumbs.contains(thumb) == false)
		{
			Component::AxisComponent* newComponent = new Component::AxisComponent();
			DSH::Input::Component::IAxisComponent* dshComponent = nullptr;
			thrower(_controller->GetComponent(_thumbMap.at(thumb), &dshComponent));
			newComponent->Setup(dshComponent);
			_thumbs[thumb] = newComponent;
		}
		*component = _thumbs.at(thumb);
	}
}

void Engine::DSHInput::Device::Controller::SetThumbStickSensitive(const long sensitive)
{
	_controller->SetThumbStickSensitive(sensitive);
}

void Engine::DSHInput::Device::Controller::SetTriggerSensitive(const long sensitive)
{
	_controller->SetTriggerSensitive(sensitive);
}

bool Engine::DSHInput::Device::Controller::IsButtonState(const Button button,
                                                         std::function<bool(DSH::Input::Component::IButtonComponent*)> state) const
{
	DSH::Input::Component::IButtonComponent* buttonComponent = nullptr;
	Utility::ThrowIfFailed()(_controller->GetComponent(_buttonMap.at(button), &buttonComponent));
	const bool result = std::invoke(state, buttonComponent);
	Utility::SafeRelease()(&buttonComponent);
	return result;
}
