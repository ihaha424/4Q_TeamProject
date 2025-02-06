#include "pch.h"
#include "DSHInputManager.h"
#include "DSHNegative.h"
#include "DSHController.h"
#include "../DSHInput/Mouse.h"

DSH::Input::MouseProcedure Engine::DSHInput::Manager::_mouseProcedure(nullptr);

LRESULT Engine::DSHInput::Manager::Procedure(const HWND windowHandle, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	return _mouseProcedure(windowHandle, message, wParam, lParam);
}

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
	mouse->SetHandle(windowHandle);
	_mouseProcedure = DSH::Input::MouseProcedure(mouse);
	_mouse.Setup(mouse);
	releaser(&mouse);

	DSH::Input::Device::IKeyboard* keyboard = nullptr;
	thrower(_system->CreateKeyboard(&keyboard));
	_keyboard.Setup(keyboard);
	releaser(&keyboard);

	DSH::Input::Device::IController* controller = nullptr;
	thrower(_system->CreateController(&controller));
	_controller.Setup(controller);
	releaser(&controller);

	DSH::Input::Modifier::INegative* negative = nullptr;
	thrower(_system->CreateModifier(&negative));
	_negative.Setup(negative);
	releaser(&negative);
}

void Engine::DSHInput::Manager::Update(const float deltaTime)
{
	_mouse.Update();
	_keyboard.Update();
	_controller.Update();
	if (_mappingContext != nullptr)	_mappingContext->Update(deltaTime);
}

void Engine::DSHInput::Manager::Reset()
{
	_mouse.Reset();
	_keyboard.Reset();
	_controller.Reset();
	if (_mappingContext != nullptr) _mappingContext->Reset();
}

void Engine::DSHInput::Manager::Finalize()
{
	_mouse.Finalize();
	_keyboard.Finalize();
	_controller.Finalize();

	_negative.Finalize();
	std::ranges::for_each(_swizzleAxes | std::views::values, [](Modifier::SwizzleAxis& swizzleAxis) { swizzleAxis.Finalize(); });
	_swizzleAxes.clear();

	std::ranges::for_each(_mappingContexts | std::views::values, [](MappingContext& mappingContext) { mappingContext.Finalize(); });
	_mappingContexts.clear();
	Utility::SafeRelease()(&_system);
}

void Engine::DSHInput::Manager::GetDevice(Input::Device::IMouse** mouse)
{
	if (mouse == nullptr) Utility::ThrowIfFailed()(E_INVALIDARG);
	else *mouse = &_mouse;
}

void Engine::DSHInput::Manager::GetDevice(Input::Device::IKeyboard** keyboard)
{
	if (keyboard == nullptr) Utility::ThrowIfFailed()(E_INVALIDARG);
	else *keyboard = &_keyboard;
}

void Engine::DSHInput::Manager::GetDevice(Input::Device::IController** controller)
{
	if (controller == nullptr) Utility::ThrowIfFailed()(E_INVALIDARG);
	else *controller = &_controller;
}

void Engine::DSHInput::Manager::GetMappingContext(const wchar_t* name, Input::IMappingContext** mappingContext)
{
	constexpr Utility::ThrowIfFailed thrower;
	if (name == nullptr || mappingContext == nullptr) thrower(E_INVALIDARG);
	else
	{
		if (_mappingContexts.contains(name) == false)
		{
			DSH::Input::IMappingContext* mappingContextPointer = nullptr;
			thrower(_system->CreateMappingContext(&mappingContextPointer));
			_mappingContexts[name].Setup(mappingContextPointer);
			Utility::SafeRelease()(&mappingContextPointer);
		}
		*mappingContext = &_mappingContexts[name];
	}
}

void Engine::DSHInput::Manager::SetActiveMappingContext(Input::IMappingContext* mappingContext)
{
	_mappingContext = reinterpret_cast<Input::MappingContext*>(mappingContext);
}

void Engine::DSHInput::Manager::GetModifier(Input::Modifier::INegative** negative)
{
	if (negative == nullptr) Utility::ThrowIfFailed()(E_INVALIDARG);
	else *negative = &_negative;
}

void Engine::DSHInput::Manager::GetModifier(const Input::Modifier::ISwizzleAxis::Type type,
	Input::Modifier::ISwizzleAxis** swizzleAxis)
{
	if (swizzleAxis == nullptr) Utility::ThrowIfFailed()(E_INVALIDARG);
	else
	{
		if (_swizzleAxes.contains(type) == false)
		{
			DSH::Input::Modifier::ISwizzleAxis* swizzleAxisPointer = nullptr;
			Utility::ThrowIfFailed()(_system->CreateModifier(&swizzleAxisPointer));
			_swizzleAxes[type].Setup(swizzleAxisPointer);
			_swizzleAxes[type].SetType(type);
			Utility::SafeRelease()(&swizzleAxisPointer);
		}
		*swizzleAxis = &_swizzleAxes[type];
	}
}
