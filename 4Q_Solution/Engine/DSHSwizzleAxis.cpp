#include "pch.h"
#include "DSHSwizzleAxis.h"

Engine::DSHInput::Modifier::SwizzleAxis::SwizzleAxis():
	_swizzleAxis(nullptr)
{
	for (unsigned char i = 0; i < static_cast<unsigned char>(Type::MAX); ++i)
	{
		_typeMap[static_cast<Type>(i)] = static_cast<DSH::Input::Modifier::ISwizzleAxis::Type>(i);
	}
}

void Engine::DSHInput::Modifier::SwizzleAxis::Setup(DSH::Input::Modifier::ISwizzleAxis* swizzleAxis)
{
	swizzleAxis->AddRef();
	_swizzleAxis = swizzleAxis;
}

void Engine::DSHInput::Modifier::SwizzleAxis::Finalize()
{
	Utility::SafeRelease()(&_swizzleAxis, "Swizzle axis is still being referenced.");
}

void Engine::DSHInput::Modifier::SwizzleAxis::SetType(const Type type)
{
	_swizzleAxis->SetType(_typeMap[type]);
}

DSH::Input::Modifier::ISwizzleAxis* Engine::DSHInput::Modifier::SwizzleAxis::Get() const
{
	return _swizzleAxis;
}
