#include "pch.h"
#include "ListenerComponent.h"
#include "DSHAudioManager.h"

Engine::Component::Listener::Listener() :
	_listener(nullptr), _up(Math::Vector3::Up), _forward(Math::Vector3::Forward)
{
}

void Engine::Component::Listener::SetForward(const Math::Vector3& forward)
{
	_forward = forward;
	Utility::ThrowIfFailed()(_listener->SetForward(forward));
}

void Engine::Component::Listener::SetUpward(const Math::Vector3& up)
{
	_up = up;
	Utility::ThrowIfFailed()(_listener->SetUp(up));
}

void Engine::Component::Listener::Initialize(const Modules& modules)
{
	Component::Initialize(modules);
	modules.audioManager->CreateListener(&_listener);
	Utility::ThrowIfFailed()(_listener->SetForward(_forward));
	Utility::ThrowIfFailed()(_listener->SetUp(_up));
}

void Engine::Component::Listener::Finalize()
{
	Component::Finalize();
	Utility::SafeRelease()(&_listener);
}

void Engine::Component::Listener::Setup(const Math::Vector3& forward, const Math::Vector3& up)
{
	_forward = forward;
	_up = up;
}

void Engine::Component::Listener::SetPosition(const Math::Vector3& position) const
{
	Utility::ThrowIfFailed()(_listener->SetPosition(position));
}

void Engine::Component::Listener::SetVelocity(const Math::Vector3& velocity) const
{
	Utility::ThrowIfFailed()(_listener->SetVelocity(velocity));
}
