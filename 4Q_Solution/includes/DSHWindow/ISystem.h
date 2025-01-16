#pragma once

namespace DSH::Window
{
	struct IClass;

	EXTERN_C const IID IID_ISystem;

	EXTERN_C MIDL_INTERFACE("88368468-2674-4441-a70a-3dc9ba5da538")
		DSH_WINDOW_LIBRARY_API ISystem : IUnknown
	{
		ISystem() = default;
		ISystem(const ISystem& other) = default;
		ISystem(ISystem&& other) noexcept = default;
		ISystem& operator=(const ISystem& other) = default;
		ISystem& operator=(ISystem&& other) noexcept = default;
		virtual ~ISystem() = default;

		virtual HRESULT STDMETHODCALLTYPE CreateClass(
			/* [annotation][in] */
			_In_ HINSTANCE hInstance,
			/* [annotation][in] */
			_In_ LPCWSTR szName,
			/* [annotation][out] */
			_Out_ IClass** ppClass) const = 0;
	};
}
