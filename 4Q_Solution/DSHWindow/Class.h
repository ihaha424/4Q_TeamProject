#pragma once

namespace DSH::Window
{
	class Class final :
	public IClass
	{
	public:
		Class(HINSTANCE instanceHandle, LPCWSTR name);

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		HRESULT Register() const override;

		HRESULT Create(RECT windowRect, IHandle** ppHandle) const override;

		void SetProcedure(LRESULT(* procedure)(HWND, UINT, WPARAM, LPARAM)) override;

	private:
		static LRESULT DefaultWindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);

		ULONG _referenceCount;

		HINSTANCE _instanceHandle;
		WNDCLASSEX _windowClass;
	};

}
