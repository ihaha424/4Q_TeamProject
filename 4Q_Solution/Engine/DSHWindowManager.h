#pragma once

namespace Engine::DSHWindow
{
	class Manager final: public Window::Manager
	{
	public:
		Manager();

		void Initialize(HINSTANCE instanceHandle, LPCWSTR name, SIZE size) override;
		void Finalize() override;

		[[nodiscard]] HWND GetHandle() const override;

		void Show(int showCommand) const override;
		void Update() const override;
		void SetCursorDefault() const override;

		void AddProcedure(WNDPROC procedure) override;

	private:
		static LRESULT WindowProcedure(HWND windowHandle, UINT message, WPARAM wParam, LPARAM lParam);
		static std::vector<WNDPROC> _windowProcedures;

		DSH::Window::ISystem* _system;
		DSH::Window::IClass* _class;
		DSH::Window::IHandle* _handle;
	};
}
