#pragma once

namespace DSH::Window
{
	class Handle final :
		public IHandle
	{
	public:
		explicit Handle(HWND windowHandle);

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		void Show() const override;
		void Show(int showCommand) const override;
		void Update() const override;
		void SetCursor(Cursor cursor) const override;
		[[nodiscard]] HWND Get() const override;

	private:
		ULONG _referenceCount;

		HWND _windowHandle;
	};
}
