#include "pch.h"
#include "Object.h"
#include "PHIObject.h"

void Engine::Object::Dispose()
{
	DisposeComponents();
	_isDispose = true;
}

bool Engine::Object::IsDisposed() const
{
	return _isDispose;
}

void Engine::Object::PreInitialize(const Modules& modules)
{
}

void Engine::Object::PostInitialize(const Modules& modules)
{
}

void Engine::Object::PreAttach()
{
}

void Engine::Object::PostAttach()
{
}

void Engine::Object::PreUpdate(float deltaTime)
{
}

void Engine::Object::PostUpdate(float deltaTime)
{
}

void Engine::Object::PreFixedUpdate()
{
}

void Engine::Object::PostFixedUpdate()
{
}

void Engine::Object::PreDetach()
{
}

void Engine::Object::PostDetach()
{
}

void Engine::Object::PreFinalize()
{
}

void Engine::Object::PostFinalize()
{
}