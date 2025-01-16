#include "pch.h"
#include "System.h"

#include "Class.h"

DSH::Window::System::System() :
	_referenceCount(1)
{
}

HRESULT DSH::Window::System::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_ISystem &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Window::System::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Window::System::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

HRESULT DSH::Window::System::CreateClass(const HINSTANCE hInstance, const LPCWSTR szName, IClass** ppClass) const
{
	if (ppClass == nullptr) E_INVALIDARG;
	Class* pClass = new Class(hInstance, szName);
	if (pClass == nullptr) return E_OUTOFMEMORY;
	*ppClass = pClass;
	return S_OK;
}
