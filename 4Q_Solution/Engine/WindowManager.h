#pragma once

namespace Engine::Window
{
	struct IManager
	{
		IManager() = default;
		IManager(const IManager& other) = default;
		IManager(IManager&& other) noexcept = default;
		IManager& operator=(const IManager& other) = default;
		IManager& operator=(IManager&& other) noexcept = default;
		virtual ~IManager() = default;

		[[nodiscard]] virtual HWND GetHandle() const = 0;
	};

	struct Manager : IManager
	{
		virtual void Initialize(HINSTANCE instanceHandle, LPCWSTR name, SIZE size) = 0;
		virtual void Finalize() = 0;

		virtual void Show(int showCommand) const = 0;
		virtual void Update() const = 0;
		virtual void SetCursorDefault() const = 0;

		virtual void AddProcedure(WNDPROC procedure) = 0;
	};
}