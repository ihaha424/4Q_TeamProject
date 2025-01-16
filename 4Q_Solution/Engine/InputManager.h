#pragma once

namespace Engine::Input
{
	struct IMappingContext;

	namespace Device
	{
		struct IMouse;
		struct IKeyboard;
		struct IController;
	}

	struct IManager
	{
		IManager() = default;
		IManager(const IManager& other) = default;
		IManager(IManager&& other) noexcept = default;
		IManager& operator=(const IManager& other) = default;
		IManager& operator=(IManager&& other) noexcept = default;
		virtual ~IManager() = default;

		virtual Device::IMouse* GetMouse() = 0;
		virtual Device::IKeyboard* GetKeyboard() = 0;
		virtual Device::IController* GetController() = 0;

		virtual IMappingContext* GetMappingContext(const wchar_t* name) = 0;
	};


	struct Manager : IManager
	{
		virtual void Initialize(HWND windowHandle) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Reset() = 0;
		virtual void Finalize() = 0;
	};
}