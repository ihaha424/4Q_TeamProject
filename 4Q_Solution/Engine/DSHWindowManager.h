#pragma once

namespace Engine::DSHWindow
{
	class Manager final: public Window::Manager
	{
	public:
		Manager() = default;

		void Initialize(HINSTANCE instanceHandle, LPCWSTR name, SIZE size) override;
		void Finalize() override;

		[[nodiscard]] HWND GetHandle() const override;

		void Show(int showCommand) const override;
		void Update() const override;
		void SetCursorDefault() const override;

	private:
		static LRESULT WindowProcedure(const HWND windowHandle, const UINT message, const WPARAM wParam, const LPARAM lParam);

		DSH::Window::ISystem* _system;
		DSH::Window::IClass* _class;
		DSH::Window::IHandle* _handle;
	};
}
