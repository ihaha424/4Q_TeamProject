#include "pch.h"
#include "DSHTimeManager.h"

void Engine::DSHTime::Manager::Initialize()
{
	constexpr Utility::ThrowIfFailed thrower;

	thrower(DSH::Time::CreateSystem()(&_system));
	thrower(_system->CreateTickTimer(&_tickTimer));
}

void Engine::DSHTime::Manager::Tick() const
{
	_tickTimer->Tick();
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
