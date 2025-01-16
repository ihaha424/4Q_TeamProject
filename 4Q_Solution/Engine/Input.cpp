#include "pch.h"
#include "Input.h"

void Engine::Manager::Input::Initialize(const HWND windowHandle)
{
	constexpr Utility::ThrowIfFailed thrower;

	thrower(DSH::Input::CreateSystem()(&_system));
	thrower(_system->CreateKeyboard(&_keyboard));
	thrower(_system->CreateMouse(&_mouse));
	_mouse->SetHandle(windowHandle);
}

void Engine::Manager::Input::Update(float deltaTime) const
{
	_keyboard->Update();
	_mouse->Update();
}

void Engine::Manager::Input::Reset() const
{
	_keyboard->Reset();
	_mouse->Reset();
}

void Engine::Manager::Input::Finalize()
{
	constexpr Utility::SafeRelease releaser;

	releaser(&_mouse, "Mouse is still being referenced.");
	releaser(&_keyboard, "Keyboard is still being referenced.");
	releaser(&_system, "Input system is still being referenced.");
}
