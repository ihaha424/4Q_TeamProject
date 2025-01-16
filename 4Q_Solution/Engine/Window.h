#pragma once

namespace Engine::Manager
{
	class Window
	{
	public:
		Window() = default;

		void Initialize(HINSTANCE instanceHandle, LPCWSTR name, SIZE size);
		void Finalize();

		void Show(int showCommand) const;
		void Update() const;
		void SetCursorDefault() const;

		[[nodiscard]] HWND GetHandle() const;

	private:
		static LRESULT WindowProcedure(const HWND windowHandle, const UINT message, const WPARAM wParam, const LPARAM lParam);

		DSH::Window::ISystem* _system;
		DSH::Window::IClass* _class;
		DSH::Window::IHandle* _handle;
	};
}

