#include "pch.h"
#include "DSHMouse.h"
#include "DSHInputButtonComponent.h"
#include "DSHInputAxisComponent.h"


Engine::DSHInput::Device::Mouse::Mouse() :
	_mouse(nullptr)
{
	for (unsigned char button = 0; button < static_cast<unsigned char>(Button::Max); ++button)
	{
		_buttonMap[static_cast<Button>(button)] = static_cast<DSH::Input::Device::IMouse::Button>(button);
	}
	for (unsigned char axis = 0; axis < static_cast<unsigned char>(Axis::Max); ++axis)
	{
		_axisMap[static_cast<Axis>(axis)] = static_cast<DSH::Input::Device::IMouse::Axis>(axis);
	}
}

void Engine::DSHInput::Device::Mouse::Setup(DSH::Input::Device::IMouse* mouse)
{
	mouse->AddRef();
	_mouse = mouse;
}

void Engine::DSHInput::Device::Mouse::Update()
{
	_mouse->Update();
}

void Engine::DSHInput::Device::Mouse::Reset()
{
	_mouse->Reset();
}

void Engine::DSHInput::Device::Mouse::Finalize()
{
	std::ranges::for_each(_buttons | std::views::values, Utility::SafeDelete());
	std::ranges::for_each(_axes | std::views::values, Utility::SafeDelete());
	Utility::SafeRelease()(&_mouse, "Mouse is still being referenced.");
}

Engine::Math::Point Engine::DSHInput::Device::Mouse::GetPosition() const
{
	const DSH::Input::Value value = _mouse->GetPosition();
	return Math::Point{ static_cast<long>(value.x), static_cast<long>(value.y) };
}

bool Engine::DSHInput::Device::Mouse::IsButtonDown(const Button button) const
{
	return IsButtonState(button, &DSH::Input::Component::IButtonComponent::IsDown);
}

bool Engine::DSHInput::Device::Mouse::IsButtonUp(const Button button) const
{
	return IsButtonState(button, &DSH::Input::Component::IButtonComponent::IsUp);
}

bool Engine::DSHInput::Device::Mouse::IsButtonPressed(const Button button) const
{
	return IsButtonState(button, &DSH::Input::Component::IButtonComponent::IsPressed);
}

bool Engine::DSHInput::Device::Mouse::IsButtonReleased(const Button button) const
{
	return IsButtonState(button, &DSH::Input::Component::IButtonComponent::IsReleased);
}

void Engine::DSHInput::Device::Mouse::GetComponent(const Button button, Input::Component::IButtonComponent** buttonComponent)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (buttonComponent == nullptr) thrower(E_INVALIDARG);
	else
	{
		if (_buttons.contains(button) == false)
		{
			Component::ButtonComponent* newButton = new Component::ButtonComponent();
			DSH::Input::Component::IButtonComponent* dButton = nullptr;
			thrower(_mouse->GetComponent(_buttonMap.at(button), &dButton));
			newButton->Setup(dButton);
			_buttons[button] = newButton;
		}
		*buttonComponent = _buttons.at(button);
	}
}

void Engine::DSHInput::Device::Mouse::GetComponent(const Axis axis, Input::Component::IAxisComponent** axisComponent)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (axisComponent == nullptr) thrower(E_INVALIDARG);
	else
	{
		if (_axes.contains(axis) == false)
		{
			Component::AxisComponent* newAxis = new Component::AxisComponent();
			DSH::Input::Component::IAxisComponent* dAxis = nullptr;
			thrower(_mouse->GetComponent(_axisMap.at(axis), &dAxis));
			newAxis->Setup(dAxis);
			_axes[axis] = newAxis;
		}
		*axisComponent = _axes.at(axis);
	}
}

void Engine::DSHInput::Device::Mouse::ShowCursor()
{
	_mouse->ShowCursor();
}

void Engine::DSHInput::Device::Mouse::HideCursor()
{
	_mouse->HideCursor();
}

void Engine::DSHInput::Device::Mouse::LockCursor()
{
	_mouse->LockCursor();
}

void Engine::DSHInput::Device::Mouse::UnlockCursor()
{
	_mouse->UnlockCursor();
}

bool Engine::DSHInput::Device::Mouse::IsButtonState(const Button button,
                                                    std::function<bool(DSH::Input::Component::IButtonComponent*)> state) const
{
	DSH::Input::Component::IButtonComponent* buttonComponent = nullptr;
	Utility::ThrowIfFailed()(_mouse->GetComponent(_buttonMap.at(button), &buttonComponent));
	const bool result = std::invoke(state, buttonComponent);
	Utility::SafeRelease()(&buttonComponent);
	return result;
}
