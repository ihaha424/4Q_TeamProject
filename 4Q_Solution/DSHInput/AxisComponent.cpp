#include "pch.h"
#include "AxisComponent.h"

#include "Value.h"

DSH::Input::Component::AxisComponent::AxisComponent() :
	_referenceCount(1), _value(0), _sensitivity(1), _deadZone(0), _absoluteValue(0), _cumulative(0)
{
}

HRESULT DSH::Input::Component::AxisComponent::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_IAxisComponent &&
		riid != IID_IComponent &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Input::Component::AxisComponent::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Input::Component::AxisComponent::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

DSH::Input::Value DSH::Input::Component::AxisComponent::GetValue() const
{
	Value value{};
	LONG absoluteValue = std::abs(_value);
	if (absoluteValue < _deadZone) return value;
	absoluteValue = (std::min)(absoluteValue, _sensitivity);
	const float scalar = static_cast<float>(absoluteValue - _deadZone) / static_cast<float>(_sensitivity - _deadZone);
	value.scalar = _value < 0 ? -scalar : scalar;
	return value;
}

void DSH::Input::Component::AxisComponent::Reset()
{
	_value = 0;
}

void DSH::Input::Component::AxisComponent::SetRelativeValue(const LONG value)
{
	_value = value;
}

void DSH::Input::Component::AxisComponent::SetAbsoluteValue(const LONG value)
{
	_value = value - _absoluteValue;
	_absoluteValue = value;
	_cumulative = _absoluteValue;
}

void DSH::Input::Component::AxisComponent::AccumulateAbsoluteValue(const LONG value)
{
	_cumulative = value - _absoluteValue;
}

void DSH::Input::Component::AxisComponent::CalculateCumulative()
{
	_value = _cumulative - _absoluteValue;
	_absoluteValue = _cumulative;
	_cumulative = _absoluteValue;

	printf("%ld\n", _value);
}

void DSH::Input::Component::AxisComponent::SetDeadZone(const LONG deadZone)
{
	_deadZone = deadZone;
}

void DSH::Input::Component::AxisComponent::SetSensitivity(const LONG sensitivity)
{
	_sensitivity = sensitivity;
}
