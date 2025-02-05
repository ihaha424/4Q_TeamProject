#pragma once
#include "InputManager.h"
#include "DSHMouse.h"
#include "DSHKeyboard.h"
#include "DSHController.h"
#include "DSHMappingContext.h"
#include "DSHNegative.h"
#include "DSHSwizzleAxis.h"

namespace Engine::DSHInput
{
	class Manager final : public Input::Manager
	{
	public:
		static LRESULT CALLBACK Procedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
	public:
		Manager();

		void Initialize(HWND windowHandle) override;
		void Update(float deltaTime) override;
		void Reset() override;
		void Finalize() override;

		void GetDevice(Input::Device::IMouse** mouse) override;
		void GetDevice(Input::Device::IKeyboard** keyboard) override;
		void GetDevice(Input::Device::IController** controller) override;

		void GetMappingContext(const wchar_t* name, Input::IMappingContext** mappingContext) override;
		void SetActiveMappingContext(Input::IMappingContext* mappingContext) override;

		void GetModifier(Input::Modifier::INegative** negative) override;
		void GetModifier(Input::Modifier::ISwizzleAxis::Type type, Input::Modifier::ISwizzleAxis** swizzleAxis) override;

	private:
		DSH::Input::ISystem* _system;

		Device::Mouse _mouse;
		Device::Keyboard _keyboard;
		Device::Controller _controller;

		Input::MappingContext* _mappingContext;

		std::unordered_map<std::wstring, MappingContext> _mappingContexts;

		Modifier::Negative _negative;
		std::unordered_map<Input::Modifier::ISwizzleAxis::Type, Modifier::SwizzleAxis> _swizzleAxes;

		static DSH::Input::MouseProcedure _mouseProcedure;
	};
}
