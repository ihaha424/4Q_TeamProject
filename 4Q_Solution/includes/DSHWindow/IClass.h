#pragma once

namespace DSH::Window
{
	struct IHandle;

	EXTERN_C const IID IID_IClass;

	EXTERN_C MIDL_INTERFACE("a8ea32f6-accb-4fde-9d3b-e5f201f21d3c")
		DSH_WINDOW_LIBRARY_API IClass : IUnknown
	{
		IClass() = default;
		IClass(const IClass& other) = default;
		IClass(IClass&& other) noexcept = default;
		IClass& operator=(const IClass& other) = default;
		IClass& operator=(IClass&& other) noexcept = default;
		virtual ~IClass() = default;

		virtual HRESULT STDMETHODCALLTYPE Register() const = 0;

		virtual HRESULT STDMETHODCALLTYPE Create(
			/* [annotation][in] */
			_In_ RECT windowRect,
			/* [annotation][out] */
			_Out_ IHandle** ppHandle) const = 0;

		virtual void STDMETHODCALLTYPE SetProcedure(
			/* [annotation][in] */
			_In_ LRESULT(*procedure)(HWND, UINT, WPARAM, LPARAM)) = 0;
	};
}
