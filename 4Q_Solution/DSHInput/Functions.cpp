#include "pch.h"
#include "Functions.h"

#include "System.h"

HRESULT DSH::Input::CreateSystem::operator()(ISystem** ppSystem) const
{
	if (ppSystem == nullptr) return E_INVALIDARG;
	System* pSystem = new System();
	if (pSystem == nullptr) return E_OUTOFMEMORY;
	*ppSystem = pSystem;
	return S_OK;
}

DSH::Input::MouseProcedure::MouseProcedure(Device::IMouse* mouse) :
	mouse(mouse)
{
	if (mouse != nullptr) mouse->UseProcedure();
}

LRESULT DSH::Input::MouseProcedure::operator()(const HWND windowHandle, const UINT message, const WPARAM wParam, const LPARAM lParam) const
{
	return mouse->Procedure(windowHandle, message, wParam, lParam);
}
