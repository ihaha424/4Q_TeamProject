#pragma once

namespace DSH::Input
{
	EXTERN_C struct DSH_INPUT_LIBRARY_API CreateSystem
	{
		HRESULT STDMETHODCALLTYPE operator()(
			/* [annotation][out] */
			_Out_ ISystem** ppSystem) const;
	};

	EXTERN_C struct DSH_INPUT_LIBRARY_API MouseProcedure
	{
		explicit MouseProcedure(Device::IMouse* mouse);

		LRESULT CALLBACK operator()(
			/* [annotation][in] */
			_In_ HWND windowHandle,
			/* [annotation][in] */
			_In_ UINT message,
			/* [annotation][in] */
			_In_ WPARAM wParam,
			/* [annotation][in] */
			_In_ LPARAM lParam) const;

		Device::IMouse* mouse;
	};
}