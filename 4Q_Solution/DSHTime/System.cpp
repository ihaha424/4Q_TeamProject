#include "pch.h"
#include "System.h"

#include "TickTimer.h"

DSH::Time::System::System()
	: _referenceCount(1)
{
}

HRESULT DSH::Time::System::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_ISystem &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Time::System::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Time::System::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

HRESULT DSH::Time::System::CreateTickTimer(ITickTimer** ppTickTimer) const
{
	if (ppTickTimer == nullptr) return E_INVALIDARG;
	TickTimer* pTickTimer = new TickTimer();
	if (pTickTimer == nullptr) return E_OUTOFMEMORY;
	*ppTickTimer = pTickTimer;
	return S_OK;
}