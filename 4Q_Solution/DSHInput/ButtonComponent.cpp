#include "pch.h"
#include "ButtonComponent.h"

#include "Value.h"

DSH::Input::Component::ButtonComponent::ButtonComponent() :
	_referenceCount(1), _value(false), _previousValue(false)
{
}

HRESULT DSH::Input::Component::ButtonComponent::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_IButtonComponent &&
		riid != IID_IComponent &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Input::Component::ButtonComponent::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Input::Component::ButtonComponent::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

DSH::Input::Value DSH::Input::Component::ButtonComponent::GetValue() const
{
	Value value{};
	value.scalar = _value ? 1.0f : 0.0f;
	return value;
}

void DSH::Input::Component::ButtonComponent::Reset()
{
	_previousValue = _value;
	_value = false;
}

void DSH::Input::Component::ButtonComponent::SetValue(const bool value)
{
	_value = value;
}

bool DSH::Input::Component::ButtonComponent::IsDown() const
{
	return _value;
}

bool DSH::Input::Component::ButtonComponent::IsUp() const
{
	return !_value;
}

bool DSH::Input::Component::ButtonComponent::IsPressed() const
{
	return _value && !_previousValue;
}

bool DSH::Input::Component::ButtonComponent::IsReleased() const
{
	return !_value && _previousValue;
}
