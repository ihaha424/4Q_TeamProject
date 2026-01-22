#pragma once

namespace DSH::Input
{
	struct IMappingContext;

	namespace Device
	{
		struct IKeyboard;
		struct IMouse;
		struct IController;
	}

	namespace Modifier
	{
		struct INegative;
		struct ISwizzleAxis;
	}

	EXTERN_C const IID IID_ISystem;

	EXTERN_C MIDL_INTERFACE("e6352f7a-9bf1-4896-8ad0-9335fe5aa1b7")
		DSH_INPUT_LIBRARY_API ISystem : IUnknown
	{
		ISystem() = default;
		ISystem(const ISystem& other) = default;
		ISystem(ISystem&& other) noexcept = default;
		ISystem& operator=(const ISystem& other) = default;
		ISystem& operator=(ISystem&& other) noexcept = default;
		virtual ~ISystem() = default;

		virtual HRESULT STDMETHODCALLTYPE CreateKeyboard(
			/* [annotation][out] */
			_Out_ Device::IKeyboard** ppKeyboard) const = 0;

		virtual HRESULT STDMETHODCALLTYPE CreateMouse(
			/* [annotation][out] */
			_Out_ Device::IMouse** ppMouse) const = 0;

		virtual HRESULT STDMETHODCALLTYPE CreateController(
			/* [annotation][out] */
			_Out_ Device::IController** ppController) const = 0;

		virtual HRESULT STDMETHODCALLTYPE CreateMappingContext(
			/* [annotation][out] */
			_Out_ IMappingContext** ppMappingContext) const = 0;

		virtual HRESULT STDMETHODCALLTYPE CreateModifier(
			/* [annotation][out] */
			_Out_ Modifier::INegative** ppModifier) const = 0;

		virtual HRESULT STDMETHODCALLTYPE CreateModifier(
			/* [annotation][out] */
			_Out_ Modifier::ISwizzleAxis** ppModifier) const = 0;
	};
}