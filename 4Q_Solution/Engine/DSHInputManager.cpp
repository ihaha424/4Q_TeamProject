#include "pch.h"
#include "DSHInputManager.h"

Engine::DSHInput::Manager::Manager() :
	_system(nullptr), _mappingContext(nullptr)
{
}

void Engine::DSHInput::Manager::Initialize(const HWND windowHandle)
{
	constexpr Utility::ThrowIfFailed thrower;
	constexpr Utility::SafeRelease releaser;

	thrower(DSH::Input::CreateSystem()(&_system));

	DSH::Input::Device::IMouse* mouse = nullptr;
	thrower(_system->CreateMouse(&mouse));
	_mouse.Setup(mouse);
	_mouse.Initialize();
	releaser(&mouse);

	// TODO: Initialize Devices;
}

void Engine::DSHInput::Manager::Update(const float deltaTime)
{
	_mouse.Update();
	// TODO: Update Devices;
	if (_mappingContext != nullptr) _mappingContext->Update(deltaTime);
}

void Engine::DSHInput::Manager::Reset()
{
	_mouse.Reset();
	// TODO: Reset Devices;
	if (_mappingContext != nullptr) _mappingContext->Reset();
}

void Engine::DSHInput::Manager::Finalize()
{
	_mouse.Finalize();
	// TODO: Finalize Devices;
	std::ranges::for_each(_mappingContexts, [](std::pair<const std::wstring, MappingContext>& mappingContext) { mappingContext.second.Finalize(); });
	_mappingContexts.clear();
	Utility::SafeRelease()(&_system);
}

Engine::Input::Device::IMouse* Engine::DSHInput::Manager::GetMouse()
{
	return &_mouse;
}

Engine::Input::Device::IKeyboard* Engine::DSHInput::Manager::GetKeyboard()
{
	// TODO: Implement GetKeyboard;
}

Engine::Input::Device::IController* Engine::DSHInput::Manager::GetController()
{
	// TODO: Implement GetController;
}

Engine::Input::IMappingContext* Engine::DSHInput::Manager::GetMappingContext(const wchar_t* name)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (name == nullptr) thrower(E_INVALIDARG);
	if (_mappingContexts.contains(name)) return &_mappingContexts[name];
	DSH::Input::IMappingContext* mappingContext = nullptr;
	thrower(_system->CreateMappingContext(&mappingContext));
	_mappingContexts[name].Setup(mappingContext);
	Utility::SafeRelease()(&mappingContext);
	return &_mappingContexts[name];
}
