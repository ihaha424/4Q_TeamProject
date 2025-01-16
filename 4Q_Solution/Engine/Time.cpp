#include "pch.h"
#include "Time.h"


void Engine::Manager::Time::Initialize()
{
	constexpr Utility::ThrowIfFailed thrower;

	thrower(DSH::Time::CreateSystem()(&_system));
	thrower(_system->CreateTickTimer(&_tickTimer));
}

void Engine::Manager::Time::Tick() const
{
	_tickTimer->Tick();
}

void Engine::Manager::Time::Finalize()
{
	constexpr Utility::SafeRelease releaser;

	releaser(&_tickTimer, "Tick timer is still being referenced.");
	releaser(&_system, "Time system is still being referenced.");
}

float Engine::Manager::Time::GetDeltaTime() const
{
	return _tickTimer->GetDeltaTime();
}

float Engine::Manager::Time::GetDeltaMetaTime() const
{
	return _tickTimer->GetDeltaMetaTime();
}
