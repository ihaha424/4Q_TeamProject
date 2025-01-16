#include "pch.h"
#include "DSHMouse.h"


Engine::DSHInput::Device::Mouse::Mouse() :
	_mouse(nullptr)
{
	_buttonMap[Button::Left] = DSH::Input::Device::IMouse::Button::Left;
	_buttonMap[Button::Right] = DSH::Input::Device::IMouse::Button::Right;
	_buttonMap[Button::Middle] = DSH::Input::Device::IMouse::Button::Middle;
	_buttonMap[Button::X1] = DSH::Input::Device::IMouse::Button::X1;
	_buttonMap[Button::X2] = DSH::Input::Device::IMouse::Button::X2;
}

void Engine::DSHInput::Device::Mouse::Setup(DSH::Input::Device::IMouse* mouse)
{
	mouse->AddRef();
	_mouse = mouse;
}

void Engine::DSHInput::Device::Mouse::Initialize()
{
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
	Utility::SafeRelease()(&_mouse, "Mouse is still being referenced.");
}

Engine::Math::Point Engine::DSHInput::Device::Mouse::GetPosition() const
{
	const DSH::Input::Value value = _mouse->GetPosition();
	return Math::Point{ static_cast<unsigned long>(value.x), static_cast<unsigned long>(value.y) };
}

bool Engine::DSHInput::Device::Mouse::IsButtonDown(Button button) const
{
	// TODO: Implement this function.
}

bool Engine::DSHInput::Device::Mouse::IsButtonUp(Button button) const
{
	// TODO: Implement this function.
}

bool Engine::DSHInput::Device::Mouse::IsButtonPressed(Button button) const
{
	// TODO: Implement this function.
}

bool Engine::DSHInput::Device::Mouse::IsButtonReleased(Button button) const
{
	// TODO: Implement this function.
}
