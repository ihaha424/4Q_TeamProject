#pragma once

namespace DSH::Input
{
	namespace Component
	{
		struct IButtonComponent;
		struct IAxisComponent;
	}

	namespace Device
	{
		EXTERN_C const IID IID_IController;

		EXTERN_C MIDL_INTERFACE("72f67b41-aa72-4b2a-84ae-9f7fb1e920c5")
			DSH_INPUT_LIBRARY_API IController : IDevice
		{
			enum class Button : unsigned char
			{
				DpadUp,
				DpadDown,
				DpadLeft,
				DpadRight,
				Start,
				Back,
				LeftThumb,
				RightThumb,
				LeftShoulder,
				RightShoulder,
				Padding1,
				Padding2,
				A,
				B,
				X,
				Y,
				Max
			};

			enum class Trigger : unsigned char
			{
				Left,
				Right,
				Max
			};

			enum class Thumb : unsigned char
			{
				LeftX,
				LeftY,
				RightX,
				RightY,
				Max
			};

			virtual void STDMETHODCALLTYPE SetControllerIndex(
				/* [annotation][in] */
				_In_ DWORD index) = 0;

			virtual HRESULT STDMETHODCALLTYPE GetComponent(
				/* [annotation][in] */
				_In_ Button button,
				/* [annotation][out] */
				_Out_ Component::IButtonComponent** ppComponent) = 0;

			virtual HRESULT STDMETHODCALLTYPE GetComponent(
				/* [annotation][in] */
				_In_ Trigger trigger,
				/* [annotation][out] */
				_Out_ Component::IAxisComponent** ppComponent) = 0;

			virtual HRESULT STDMETHODCALLTYPE GetComponent(
				/* [annotation][in] */
				_In_ Thumb thumb,
				/* [annotation][out] */
				_Out_ Component::IAxisComponent** ppComponent) = 0;

			virtual void STDMETHODCALLTYPE SetThumbStickSensitive(
				/* [annotation][in] */
				_In_ LONG sensitive) = 0;

			virtual void STDMETHODCALLTYPE SetTriggerSensitive(
				/* [annotation][in] */
				_In_ LONG sensitive) = 0;
		};
	}
}
