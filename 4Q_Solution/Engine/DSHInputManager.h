#pragma once
#include "InputManager.h"
#include "DSHMouse.h"
#include "DSHMappingContext.h"

namespace Engine::DSHInput
{
	class Manager final : public Input::Manager
	{
	public:
		Manager();

		void Initialize(HWND windowHandle) override;
		void Update(float deltaTime) override;
		void Reset() override;
		void Finalize() override;

		Input::Device::IMouse* GetMouse() override;
		Input::Device::IKeyboard* GetKeyboard() override;
		Input::Device::IController* GetController() override;

		Input::IMappingContext* GetMappingContext(const wchar_t* name) override;

	private:
		DSH::Input::ISystem* _system;
		Device::Mouse _mouse;

		MappingContext* _mappingContext;

		std::unordered_map<std::wstring, MappingContext> _mappingContexts;
	};
}
