#pragma once

namespace DSH::Input::Device
{
	EXTERN_C const IID IID_IDevice;

	EXTERN_C MIDL_INTERFACE("1ac556e1-cf43-4fdd-acef-74ed1b783743")
		DSH_INPUT_LIBRARY_API IDevice : IUnknown
	{
		IDevice() = default;
		IDevice(const IDevice& other) = default;
		IDevice(IDevice&& other) noexcept = default;
		IDevice& operator=(const IDevice& other) = default;
		IDevice& operator=(IDevice&& other) noexcept = default;
		virtual ~IDevice() = default;

		virtual void STDMETHODCALLTYPE Update() = 0;

		virtual void STDMETHODCALLTYPE Reset() = 0;
	};
}