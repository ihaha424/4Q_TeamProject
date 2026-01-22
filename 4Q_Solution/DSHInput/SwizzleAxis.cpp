#include "pch.h"
#include "SwizzleAxis.h"
#include "Value.h"

DSH::Input::Modifier::SwizzleAxis::SwizzleAxis() :
	_referenceCount(1), _type(Type::XYZ)
{
}

HRESULT DSH::Input::Modifier::SwizzleAxis::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_ISwizzleAxis &&
		riid != IID_IModifier &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Input::Modifier::SwizzleAxis::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Input::Modifier::SwizzleAxis::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

DSH::Input::Value DSH::Input::Modifier::SwizzleAxis::Modify(const Value value) const
{
	Value result{};
	switch (_type)
	{
	case Type::XYZ:
		result.x = value.x;
		result.y = value.y;
		result.z = value.z;
		break;
	case Type::XZY:
		result.x = value.x;
		result.z = value.y;
		result.y = value.z;
		break;
	case Type::YXZ:
		result.y = value.x;
		result.x = value.y;
		result.z = value.z;
		break;
	case Type::YZX:
		result.y = value.x;
		result.z = value.y;
		result.x = value.z;
		break;
	case Type::ZXY:
		result.z = value.x;
		result.x = value.y;
		result.y = value.z;
		break;
	case Type::ZYX:
		result.z = value.x;
		result.y = value.y;
		result.x = value.z;
		break;
	}
	return result;
}

void DSH::Input::Modifier::SwizzleAxis::SetType(Type type)
{
	_type = type;
}
