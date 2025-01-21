#include "pch.h"
#include "DSHInputManager.h"
#include "DSHNegative.h"
#include "DSHController.h"

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

	DSH::Input::Device::IKeyboard* keyboard = nullptr;
	thrower(_system->CreateKeyboard(&keyboard));
	_keyboard.Setup(keyboard);
	_keyboard.Initialize();
	releaser(&keyboard);

	DSH::Input::Device::IController* controller = nullptr;
	thrower(_system->CreateController(&controller));
	_controller.Setup(controller);
	_controller.Initialize();
	releaser(&controller);

	DSH::Input::Modifier::INegative* negative = nullptr;
	thrower(_system->CreateModifier(&negative));
	_negative.Setup(negative);
	releaser(&negative);
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

	_negative.Finalize();
	std::ranges::for_each(_swizzleAxes, [](std::pair<const Input::Modifier::ISwizzleAxis::Type, Modifier::SwizzleAxis>& swizzleAxis) { swizzleAxis.second.Finalize(); });
	_swizzleAxes.clear();

	std::ranges::for_each(_mappingContexts, [](std::pair<const std::wstring, MappingContext>& mappingContext) { mappingContext.second.Finalize(); });
	_mappingContexts.clear();
	Utility::SafeRelease()(&_system);
}

void Engine::DSHInput::Manager::GetDevice(Input::Device::IMouse** mouse)
{
	if (mouse == nullptr) Utility::ThrowIfFailed()(E_INVALIDARG);
	*mouse = &_mouse;
}

void Engine::DSHInput::Manager::GetDevice(Input::Device::IKeyboard** keyboard)
{
	if (keyboard == nullptr) Utility::ThrowIfFailed()(E_INVALIDARG);
	*keyboard = &_keyboard;
}

void Engine::DSHInput::Manager::GetDevice(Input::Device::IController** controller)
{
	if (controller == nullptr) Utility::ThrowIfFailed()(E_INVALIDARG);
	*controller = &_controller;
}

void Engine::DSHInput::Manager::GetMappingContext(const wchar_t* name, Input::IMappingContext** mappingContext)
{
	if (name == nullptr) Utility::ThrowIfFailed()(E_INVALIDARG);
	if (mappingContext == nullptr) Utility::ThrowIfFailed()(E_INVALIDARG);
	if (_mappingContexts.contains(name)) *mappingContext = &_mappingContexts[name];
	DSH::Input::IMappingContext* mappingContextPointer = nullptr;
	Utility::ThrowIfFailed()(_system->CreateMappingContext(&mappingContextPointer));
	_mappingContexts[name].Setup(mappingContextPointer);
	Utility::SafeRelease()(&mappingContextPointer);
	*mappingContext = &_mappingContexts[name];
}

void Engine::DSHInput::Manager::SetActiveMappingContext(Input::IMappingContext* mappingContext)
{
	_mappingContext = static_cast<MappingContext*>(mappingContext);
}

void Engine::DSHInput::Manager::GetModifier(Input::Modifier::INegative** negative)
{
	if (negative == nullptr) Utility::ThrowIfFailed()(E_INVALIDARG);
	*negative = &_negative;
}

void Engine::DSHInput::Manager::GetModifier(const Input::Modifier::ISwizzleAxis::Type type,
	Input::Modifier::ISwizzleAxis** swizzleAxis)
{
	if (swizzleAxis == nullptr) Utility::ThrowIfFailed()(E_INVALIDARG);
	if (_swizzleAxes.contains(type)) *swizzleAxis = &_swizzleAxes[type];
	DSH::Input::Modifier::ISwizzleAxis* swizzleAxisPointer = nullptr;
	Utility::ThrowIfFailed()(_system->CreateModifier(&swizzleAxisPointer));
	_swizzleAxes[type].Setup(swizzleAxisPointer);
	Utility::SafeRelease()(&swizzleAxisPointer);
	*swizzleAxis = &_swizzleAxes[type];
}
