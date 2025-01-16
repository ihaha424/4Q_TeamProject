#include "pch.h"
#include "Functions.h"

#include "System.h"

HRESULT DSH::Window::CreateSystem::operator()(ISystem** ppSystem) const
{
    if (ppSystem == nullptr) return E_INVALIDARG;
    System* pSystem = new System();
    if (pSystem == nullptr) return E_OUTOFMEMORY;
    *ppSystem = pSystem;
    return S_OK;
}

HRESULT DSH::Window::AdjustWindowRect::operator()(const SIZE size, RECT* pRect) const
{
    *pRect = { .left= 0, .top= 0, .right= size.cx, .bottom= size.cy};
    return operator()(pRect);
}

HRESULT DSH::Window::AdjustWindowRect::operator()(RECT* pRect) const
{
    if (const BOOL result = ::AdjustWindowRect(pRect, WS_OVERLAPPEDWINDOW, FALSE); result == FALSE)
    {
        const DWORD error = GetLastError();
        return HRESULT_FROM_WIN32(error);
    }
    return S_OK;
}