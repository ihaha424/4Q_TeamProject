#pragma once

namespace Engine::Manager
{
	struct IWindow
	{
		IWindow() = default;
		IWindow(const IWindow& other) = default;
		IWindow(IWindow&& other) noexcept = default;
		IWindow& operator=(const IWindow& other) = default;
		IWindow& operator=(IWindow&& other) noexcept = default;
		virtual ~IWindow() = default;

		[[nodiscard]] virtual HWND GetHandle() const = 0;
	};

	class Window final : public IWindow
	{
	public:
		Window() = default;

		void Initialize(HINSTANCE instanceHandle, LPCWSTR name, SIZE size);
		void Finalize();

		void Show(int showCommand) const;
		void Update() const;
		void SetCursorDefault() const;

		[[nodiscard]] HWND GetHandle() const override;

	private:
		static LRESULT WindowProcedure(const HWND windowHandle, const UINT message, const WPARAM wParam, const LPARAM lParam);

		DSH::Window::ISystem* _system;
		DSH::Window::IClass* _class;
		DSH::Window::IHandle* _handle;
	};
}

