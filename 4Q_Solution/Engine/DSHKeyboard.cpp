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

void Engine::DSHInput::Device::Keyboard::Initialize()
{
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

bool Engine::DSHInput::Device::Keyboard::IsKeyDown(Key key) const
{
	// TODO: Implement this function.
	return false;
}

bool Engine::DSHInput::Device::Keyboard::IsKeyUp(Key key) const
{
	// TODO: Implement this function.
	return false;
}

bool Engine::DSHInput::Device::Keyboard::IsKeyPressed(Key key) const
{
	// TODO: Implement this function.
	return false;
}

bool Engine::DSHInput::Device::Keyboard::IsKeyReleased(Key key) const
{
	// TODO: Implement this function.
	return false;
}

void Engine::DSHInput::Device::Keyboard::GetComponent(const Key key, Input::Component::IButtonComponent** button)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (button == nullptr) thrower(E_INVALIDARG);
	else
	{
		if (_buttons.contains(key) == false)
		{
			Component::ButtonComponent* newButton = new Component::ButtonComponent();
			DSH::Input::Component::IButtonComponent* dButton = nullptr;
			thrower(_keyboard->GetComponent(_keyMap[key], &dButton));
			newButton->Setup(dButton);
			_buttons[key] = newButton;
		}
		*button = _buttons[key];
	}
}
