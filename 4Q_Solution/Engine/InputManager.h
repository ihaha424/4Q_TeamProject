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

	namespace Modifier
	{
		struct INegative;
		struct ISwizzleAxis;
	}

	struct IManager
	{
		IManager() = default;
		IManager(const IManager& other) = default;
		IManager(IManager&& other) noexcept = default;
		IManager& operator=(const IManager& other) = default;
		IManager& operator=(IManager&& other) noexcept = default;
		virtual ~IManager() = default;

		virtual void GetDevice(Device::IMouse** mouse) = 0;
		virtual void GetDevice(Device::IKeyboard** keyboard) = 0;
		virtual void GetDevice(Device::IController** controller) = 0;

		virtual void GetMappingContext(const wchar_t* name, IMappingContext** mappingContext) = 0;

		virtual void GetModifier(Modifier::INegative** negative) = 0;
		virtual void GetModifier(Modifier::ISwizzleAxis::Type type, Modifier::ISwizzleAxis** swizzleAxis) = 0;
	};


	struct Manager : IManager
	{
		virtual void Initialize(HWND windowHandle) = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void Reset() = 0;
		virtual void Finalize() = 0;
	};
}