#include "pch.h"
#include "Class.h"

#include "Handle.h"

DSH::Window::Class::Class(const HINSTANCE instanceHandle, const LPCWSTR name) :
	_referenceCount(1), _instanceHandle(instanceHandle), _windowClass{
		sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, DefaultWindowProcedure,
		  NULL, NULL, instanceHandle, LoadIcon(instanceHandle, IDI_APPLICATION),
		  LoadCursor(instanceHandle, IDC_ARROW), static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)),
		  nullptr, name, LoadIcon(instanceHandle, IDI_APPLICATION)
	}
{
}

HRESULT DSH::Window::Class::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_IClass &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;

}

ULONG DSH::Window::Class::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Window::Class::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

HRESULT DSH::Window::Class::Register() const
{
	if (const ATOM result = RegisterClassEx(&_windowClass); result == NULL)
	{
		const DWORD error = GetLastError();
		return HRESULT_FROM_WIN32(error);
	}

	return S_OK;
}

HRESULT DSH::Window::Class::Create(const RECT windowRect, IHandle** ppHandle) const
{
	if (ppHandle == nullptr) return E_INVALIDARG;
	const HWND handle = CreateWindow(_windowClass.lpszClassName, _windowClass.lpszClassName,
		WS_OVERLAPPEDWINDOW, windowRect.left, windowRect.top, windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top, nullptr, nullptr, _instanceHandle, nullptr);
	if (handle == nullptr)
	{
		const DWORD error = GetLastError();
		return HRESULT_FROM_WIN32(error);
	}
	Handle* pHandle = new Handle(handle);
	if (pHandle == nullptr) return E_OUTOFMEMORY;
	*ppHandle = pHandle;
	return S_OK;
}

void DSH::Window::Class::SetProcedure(LRESULT(*procedure)(HWND, UINT, WPARAM, LPARAM))
{
	_windowClass.lpfnWndProc = procedure;
}

LRESULT DSH::Window::Class::DefaultWindowProcedure(const HWND windowHandle, const UINT message, const WPARAM wParam, const LPARAM lParam)
{
	if (message == WM_DESTROY)
	{
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(windowHandle, message, wParam, lParam);
}