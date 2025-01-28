#include "pch.h"
#include "DSHTimeManager.h"

Engine::DSHTime::Manager::Manager():
	_system(nullptr), _tickTimer(nullptr), _elapsedTime(0), _fixedUpdateInterval(0)
{
}

void Engine::DSHTime::Manager::Initialize(const float fixedUpdateInterval)
{
	constexpr Utility::ThrowIfFailed thrower;

	thrower(DSH::Time::CreateSystem()(&_system));
	thrower(_system->CreateTickTimer(&_tickTimer));
	_fixedUpdateInterval = fixedUpdateInterval;
}

void Engine::DSHTime::Manager::Tick()
{
	_tickTimer->Tick();
	_elapsedTime += _tickTimer->GetDeltaTime();
}

bool Engine::DSHTime::Manager::IsFixedUpdate()
{
	if (_elapsedTime >= _fixedUpdateInterval)
	{
		_elapsedTime -= _fixedUpdateInterval;
		return true;
	}
	return false;
}

void Engine::DSHTime::Manager::Finalize()
{
	constexpr Utility::SafeRelease releaser;

	releaser(&_tickTimer, "Tick timer is still being referenced.");
	releaser(&_system, "Time system is still being referenced.");
}

float Engine::DSHTime::Manager::GetDeltaTime() const
{
	return _tickTimer->GetDeltaTime();
}

float Engine::DSHTime::Manager::GetDeltaMetaTime() const
{
	return _tickTimer->GetDeltaMetaTime();
}
