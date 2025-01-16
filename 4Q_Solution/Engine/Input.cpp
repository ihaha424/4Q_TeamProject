#include "pch.h"
#include "Input.h"

void Engine::Manager::Input::Initialize(const HWND windowHandle)
{
	constexpr Utility::ThrowIfFailed thrower;

	thrower(DSH::Input::CreateSystem()(&_system));
	thrower(_system->CreateMappingContext(&_mappingContext));
	thrower(_system->CreateKeyboard(&_keyboard));
	thrower(_system->CreateMouse(&_mouse));
	_mouse->SetHandle(windowHandle);
}

void Engine::Manager::Input::Update(const float deltaTime) const
{
	_keyboard->Update();
	_mouse->Update();
	_mappingContext->Update(deltaTime);

}

void Engine::Manager::Input::Reset() const
{
	_keyboard->Reset();
	_mouse->Reset();
	_mappingContext->Reset();
}

void Engine::Manager::Input::Finalize()
{
	constexpr Utility::SafeRelease releaser;

	releaser(&_mouse, "Mouse is still being referenced.");
	releaser(&_keyboard, "Keyboard is still being referenced.");
	releaser(&_mappingContext, "Mapping context is still being referenced.");
	releaser(&_system, "Input system is still being referenced.");
}

void Engine::Manager::Input::AddActionListener(const std::wstring_view actionName, const DSH::Input::Trigger::Event event,
	const std::function<void(DSH::Input::Value value)>& listener)
{
	DSH::Input::IAction* action = nullptr;
	Utility::ThrowIfFailed()(_mappingContext->GetAction(actionName.data(), &action));
	action->AddListener(event, listener);
}

DSH::Input::IMappingContext* Engine::Manager::Input::GetMappingContext()
{
	return _mappingContext;
}

DSH::Input::Device::IKeyboard* Engine::Manager::Input::GetKeyboard()
{
	return _keyboard;
}

DSH::Input::ISystem* Engine::Manager::Input::GetSystem()
{
	return _system;
}
