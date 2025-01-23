#include "pch.h"
#include "DSHWindowManager.h"

Engine::DSHWindow::Manager::Manager():
	_system(nullptr), _class(nullptr), _handle(nullptr)
{
}

void Engine::DSHWindow::Manager::Initialize(const HINSTANCE instanceHandle, const LPCWSTR name, const SIZE size)
{
	constexpr Utility::ThrowIfFailed thrower;

	thrower(DSH::Window::CreateSystem()(&_system));

	thrower(_system->CreateClass(instanceHandle, name, &_class));
	_class->SetProcedure(WindowProcedure);
	thrower(_class->Register());

	RECT rect
	{
		.left = 0,
		.top = 0,
		.right = size.cx,
		.bottom = size.cy
	};

	thrower(DSH::Window::AdjustWindowRect()(&rect));
	thrower(_class->Create(rect, &_handle));
}

void Engine::DSHWindow::Manager::Finalize()
{
	constexpr Utility::SafeRelease releaser;

	releaser(&_handle, "Window handle is still being referenced.");
	releaser(&_class, "Window class is still being referenced.");
	releaser(&_system, "Window system is still being referenced.");
}

HWND Engine::DSHWindow::Manager::GetHandle() const
{
	return _handle->Get();
}

void Engine::DSHWindow::Manager::Show(const int showCommand) const
{
	_handle->Show(showCommand);
}

void Engine::DSHWindow::Manager::Update() const
{
	_handle->Update();
}

void Engine::DSHWindow::Manager::SetCursorDefault() const
{
	_handle->SetCursor(DSH::Window::IHandle::Cursor::Arrow);
}

extern void PlaceInCenterOfScreen(const HWND windowHandle)
{
	const int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	const int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	RECT rect;
	GetClientRect(windowHandle, &rect);
	::AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, FALSE);
	const int clientWidth = rect.right - rect.left;
	const int clientHeight = rect.bottom - rect.top;
	SetWindowPos(windowHandle, nullptr, screenWidth / 2 - clientWidth / 2, screenHeight / 2 - clientHeight / 2,
		clientWidth, clientHeight, NULL);
}


LRESULT Engine::DSHWindow::Manager::WindowProcedure(const HWND windowHandle, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	switch (message)
	{
	case WM_CREATE:
		PlaceInCenterOfScreen(windowHandle);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(windowHandle, message, wParam, lParam);
}
