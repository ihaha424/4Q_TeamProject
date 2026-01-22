#include "pch.h"
#include "Negative.h"
#include "Value.h"

DSH::Input::Modifier::Negative::Negative() :
	_referenceCount(1)
{
}

HRESULT DSH::Input::Modifier::Negative::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_INegative &&
		riid != IID_IModifier &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Input::Modifier::Negative::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Input::Modifier::Negative::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

DSH::Input::Value DSH::Input::Modifier::Negative::Modify(const Value value) const
{
	Value result{};
	result.x = -value.x;
	result.y = -value.y;
	result.z = -value.z;
	return result;
}
