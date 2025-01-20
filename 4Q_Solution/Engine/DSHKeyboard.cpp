#include "pch.h"
#include "DSHKeyboard.h"

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
	Utility::SafeRelease()(&_keyboard, "Keyboard is still being referenced.");
}

bool Engine::DSHInput::Device::Keyboard::IsKeyDown(Key key) const
{
	// TODO: Implement this function.
}

bool Engine::DSHInput::Device::Keyboard::IsKeyUp(Key key) const
{
	// TODO: Implement this function.
}

bool Engine::DSHInput::Device::Keyboard::IsKeyPressed(Key key) const
{
	// TODO: Implement this function.
}

bool Engine::DSHInput::Device::Keyboard::IsKeyReleased(Key key) const
{
	// TODO: Implement this function.
}
