#include "pch.h"
#include "System.h"

#include "Controller.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "MappingContext.h"
#include "Negative.h"
#include "SwizzleAxis.h"

DSH::Input::System::System() :
	_referenceCount(1)
{
}


HRESULT DSH::Input::System::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_ISystem &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Input::System::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Input::System::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

HRESULT DSH::Input::System::CreateKeyboard(Device::IKeyboard** ppKeyboard) const
{
	if (ppKeyboard == nullptr) return E_INVALIDARG;
	Device::Keyboard* pKeyboard = new Device::Keyboard();
	if (pKeyboard == nullptr) return E_OUTOFMEMORY;
	*ppKeyboard = pKeyboard;
	return S_OK;
}

HRESULT DSH::Input::System::CreateMouse(Device::IMouse** ppMouse) const
{
	if (ppMouse == nullptr) return E_INVALIDARG;
	Device::Mouse* pMouse = new Device::Mouse();
	if (pMouse == nullptr) return E_OUTOFMEMORY;
	*ppMouse = pMouse;
	return S_OK;
}

HRESULT DSH::Input::System::CreateController(Device::IController** ppController) const
{
	if (ppController == nullptr) return E_INVALIDARG;
	Device::Controller* pController = new Device::Controller();
	if (pController == nullptr) return E_OUTOFMEMORY;
	*ppController = pController;
	return S_OK;
}

HRESULT DSH::Input::System::CreateMappingContext(IMappingContext** ppMappingContext) const
{
	if (ppMappingContext == nullptr) return E_INVALIDARG;
	MappingContext* pMappingContext = new MappingContext();
	if (pMappingContext == nullptr) return E_OUTOFMEMORY;
	*ppMappingContext = pMappingContext;
	return S_OK;
}

HRESULT DSH::Input::System::CreateModifier(Modifier::INegative** ppModifier) const
{
	if (ppModifier == nullptr) return E_INVALIDARG;
	Modifier::Negative* pModifier = new Modifier::Negative();
	if (pModifier == nullptr) return E_OUTOFMEMORY;
	*ppModifier = pModifier;
	return S_OK;
}

HRESULT DSH::Input::System::CreateModifier(Modifier::ISwizzleAxis** ppModifier) const
{
	if (ppModifier == nullptr) return E_INVALIDARG;
	Modifier::SwizzleAxis* pModifier = new Modifier::SwizzleAxis();
	if (pModifier == nullptr) return E_OUTOFMEMORY;
	*ppModifier = pModifier;
	return S_OK;
}
