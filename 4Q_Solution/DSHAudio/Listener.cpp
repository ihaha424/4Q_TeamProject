#include "pch.h"
#include "Listener.h"

#include "Helper.h"

DSH::Audio::Listener::Listener(FMOD::System* system, const int index) :
	_referenceCount(1), _system(system), _index(index)
{
}

HRESULT DSH::Audio::Listener::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_IListener &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Audio::Listener::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Audio::Listener::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

HRESULT DSH::Audio::Listener::Activate()
{
	return Helper::FmodResultToHResult()(_system->set3DListenerAttributes(_index, &_position, &_velocity, &_forward, &_up));
}


HRESULT DSH::Audio::Listener::SetPosition(const Vector& position)
{
	_position = position;
	return Activate();
}

HRESULT DSH::Audio::Listener::SetVelocity(const Vector& velocity)
{
	_velocity = velocity;
	return Activate();
}

HRESULT DSH::Audio::Listener::SetForward(const Vector& forward)
{
	_forward = forward;
	return Activate();
}

HRESULT DSH::Audio::Listener::SetUp(const Vector& up)
{
	_up = up;
	return Activate();
}
