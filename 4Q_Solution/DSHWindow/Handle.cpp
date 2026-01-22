#include "pch.h"
#include "Handle.h"

DSH::Window::Handle::Handle(const HWND windowHandle) :
	_referenceCount(1), _windowHandle(windowHandle)
{
}

HRESULT DSH::Window::Handle::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_IHandle &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Window::Handle::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Window::Handle::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

void DSH::Window::Handle::Show() const
{
	Show(SW_NORMAL);
}

void DSH::Window::Handle::Show(const int showCommand) const
{
	ShowWindow(_windowHandle, showCommand);
}

void DSH::Window::Handle::Update() const
{
	UpdateWindow(_windowHandle);
}

void DSH::Window::Handle::SetCursor(Cursor cursor) const
{
	::SetCursor(LoadCursor(nullptr, MAKEINTRESOURCE(cursor)));
}

HWND DSH::Window::Handle::Get() const
{
	return _windowHandle;
}
