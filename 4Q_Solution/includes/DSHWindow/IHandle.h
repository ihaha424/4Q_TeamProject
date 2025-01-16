#pragma once

namespace DSH::Window
{
	EXTERN_C const IID IID_IHandle;

	MIDL_INTERFACE("648bc7be-2d59-4743-b5d6-f0f3be13df6c")
		DSH_WINDOW_LIBRARY_API IHandle : IUnknown
	{
		enum class Cursor : unsigned short
		{
			Arrow = 32512,
			IBeam = 32513,
			Wait = 32514,
			Cross = 32515,
			UpArrow = 32516,
			Size = 32640,
			Icon = 32641,
			SizeNWSE = 32642,
			SizeNESW = 32643,
			SizeWE = 32644,
			SizeNS = 32645,
			SizeAll = 32646,
			No = 32648,
			Hand = 32649,
			AppStarting = 32650,
			Help = 32651,
			Pin = 32671,
			Person = 32672
		};

		IHandle() = default;
		IHandle(const IHandle& other) = default;
		IHandle(IHandle&& other) noexcept = default;
		IHandle& operator=(const IHandle& other) = default;
		IHandle& operator=(IHandle&& other) noexcept = default;
		virtual ~IHandle() = default;

		virtual void STDMETHODCALLTYPE Show() const = 0;

		virtual void STDMETHODCALLTYPE Show(
			/* [annotation][in] */
			_In_ int showCommand) const = 0;

		virtual void STDMETHODCALLTYPE Update() const = 0;

		virtual void STDMETHODCALLTYPE SetCursor(
			/* [annotation][in] */
			_In_ Cursor cursor) const = 0;

		[[nodiscard]] virtual HWND STDMETHODCALLTYPE Get() const = 0;
	};
}
