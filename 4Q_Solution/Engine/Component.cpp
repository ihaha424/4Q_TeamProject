#include "pch.h"
#include "Component.h"

void Engine::Component::Component::Dispose()
{
	_isDispose = true;
}

bool Engine::Component::Component::IsDisposed() const
{
	return _isDispose;
}

void Engine::Component::Component::Initialize(const Modules& modules)
{
}

void Engine::Component::Component::Attach()
{
}

void Engine::Component::Component::Update(float deltaTime)
{
}

void Engine::Component::Component::FixedUpdate()
{
}

void Engine::Component::Component::Detach()
{
}

void Engine::Component::Component::Finalize()
{
}