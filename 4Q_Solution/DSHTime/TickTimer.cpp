#include "pch.h"
#include "TickTimer.h"

DSH::Time::TickTimer::TickTimer():
_referenceCount(1), _deltaTime(0.0f), _timeScale(1.0f)
{
	_currentTime = std::chrono::steady_clock::now();
}

HRESULT DSH::Time::TickTimer::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_ITickTimer &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Time::TickTimer::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Time::TickTimer::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

void DSH::Time::TickTimer::Tick() noexcept
{
	_previousTime = _currentTime;
	_currentTime = std::chrono::steady_clock::now();
	_deltaTime = std::chrono::duration<float>(_currentTime - _previousTime).count();
}

FLOAT DSH::Time::TickTimer::GetDeltaMetaTime() const noexcept
{
	return _deltaTime;
}

FLOAT DSH::Time::TickTimer::GetDeltaTime() const noexcept
{
	return _deltaTime * _timeScale;
}

FLOAT DSH::Time::TickTimer::SetTimeScale(const FLOAT timeScale) noexcept
{
	const float previousTimeScale = _timeScale;
	_timeScale = timeScale;
	return previousTimeScale;
}

FLOAT DSH::Time::TickTimer::GetTimeScale() const noexcept
{
	return _timeScale;
}
