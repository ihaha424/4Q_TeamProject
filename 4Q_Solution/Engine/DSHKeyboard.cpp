#include "pch.h"
#include "DSHKeyboard.h"
#include "DSHInputButtonComponent.h"

Engine::DSHInput::Device::Keyboard::Keyboard():
	_keyboard(nullptr)
{
	for (unsigned char key = 0; key < static_cast<unsigned char>(Key::Max); ++key )
	{
		_keyMap[static_cast<Key>(key)] = static_cast<DSH::Input::Device::IKeyboard::Key>(key);
	}
}

void Engine::DSHInput::Device::Keyboard::Setup(DSH::Input::Device::IKeyboard* keyboard)
{
	keyboard->AddRef();
	_keyboard = keyboard;
}

void Engine::DSHInput::Device::Keyboard::Update()
{
	_keyboard->Update();
}

void Engine::DSHInput::Device::Keyboard::Reset()
{
	_keyboard->Reset();
}

void Engine::DSHInput::Device::Keyboard::Finalize()
{
	std::ranges::for_each(_buttons | std::views::values, Utility::SafeDelete());
	Utility::SafeRelease()(&_keyboard, "Keyboard is still being referenced.");
}

bool Engine::DSHInput::Device::Keyboard::IsKeyDown(const Key key) const
{
	return IsButtonState(key, &DSH::Input::Component::IButtonComponent::IsDown);
}

bool Engine::DSHInput::Device::Keyboard::IsKeyUp(const Key key) const
{
	return IsButtonState(key, &DSH::Input::Component::IButtonComponent::IsUp);
}

bool Engine::DSHInput::Device::Keyboard::IsKeyPressed(const Key key) const
{
	return IsButtonState(key, &DSH::Input::Component::IButtonComponent::IsPressed);
}

bool Engine::DSHInput::Device::Keyboard::IsKeyReleased(const Key key) const
{
	return IsButtonState(key, &DSH::Input::Component::IButtonComponent::IsReleased);
}

void Engine::DSHInput::Device::Keyboard::GetComponent(const Key key, Input::Component::IButtonComponent** buttonComponent)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (buttonComponent == nullptr) thrower(E_INVALIDARG);
	else
	{
		if (_buttons.contains(key) == false)
		{
			Component::ButtonComponent* newButton = new Component::ButtonComponent();
			DSH::Input::Component::IButtonComponent* dButton = nullptr;
			thrower(_keyboard->GetComponent(_keyMap.at(key), &dButton));
			newButton->Setup(dButton);
			_buttons[key] = newButton;
		}
		*buttonComponent = _buttons.at(key);
	}
}

bool Engine::DSHInput::Device::Keyboard::IsButtonState(const Key key,
	std::function<bool(DSH::Input::Component::IButtonComponent*)> state) const
{
	DSH::Input::Component::IButtonComponent* buttonComponent = nullptr;
	Utility::ThrowIfFailed()(_keyboard->GetComponent(_keyMap.at(key), &buttonComponent));
	const bool result = std::invoke(state, buttonComponent);
	Utility::SafeRelease()(&buttonComponent);
	return result;
}
