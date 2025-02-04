#pragma once

namespace DSH::Input
{
	union Value;
	namespace Component
	{
		struct IButtonComponent;
		struct IAxisComponent;
	}

	namespace Device
	{
		EXTERN_C const IID IID_IMouse;

		EXTERN_C MIDL_INTERFACE("00228a73-ecf0-4fc3-96f3-f08d448befd0")
			DSH_INPUT_LIBRARY_API IMouse : IDevice
		{

			enum class Button : unsigned char
			{
				Left = VK_LBUTTON,
				Right = VK_RBUTTON,
				Middle = VK_MBUTTON,
				X1 = VK_XBUTTON1,
				X2 = VK_XBUTTON2,
				Max = 0x07
			};

			enum class Axis : unsigned char
			{
				X,
				Y,
				Wheel,
				Max
			};

			virtual LRESULT CALLBACK Procedure(
				/* [annotation][in] */
				_In_ HWND windowHandle,
				/* [annotation][in] */
				_In_ UINT message,
				/* [annotation][in] */
				_In_ WPARAM wParam,
				/* [annotation][in] */
				_In_ LPARAM lParam) = 0;

			virtual void UseProcedure() = 0;

			virtual void STDMETHODCALLTYPE SetHandle(
				HWND handle) = 0;

			virtual HRESULT STDMETHODCALLTYPE GetComponent(
				/* [annotation][in] */
				_In_ Button button,
				/* [annotation][out] */
				_Out_ Component::IButtonComponent** ppComponent) = 0;

			virtual HRESULT STDMETHODCALLTYPE GetComponent(
				/* [annotation][in] */
				_In_ Axis axis,
				/* [annotation][out] */
				_Out_ Component::IAxisComponent** ppComponent) = 0;

			[[nodiscard]] virtual Value STDMETHODCALLTYPE GetPosition() const = 0;

			virtual void STDMETHODCALLTYPE ShowCursor() = 0;

			virtual void STDMETHODCALLTYPE HideCursor() = 0;

			virtual void STDMETHODCALLTYPE LockCursor() = 0;

			virtual void STDMETHODCALLTYPE UnlockCursor() = 0;
		};
	}
}
