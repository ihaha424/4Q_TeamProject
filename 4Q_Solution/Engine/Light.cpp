#include "pch.h"
#include "Light.h"
#include "GEGraphicsManager.h"

Engine::Component::Light::Light()
	: _geLight(nullptr)
{
}

void Engine::Component::Light::Initialize(const Modules& modules)
{
	GraphicsComponent::Initialize(modules);
	auto lightSystem = _graphicsManager->GetLightSystem();
	lightSystem->CreateLight(&_geLight);
}

void Engine::Component::Light::Attach()
{
	Component::Attach();
	auto lightSystem = _graphicsManager->GetLightSystem();
	lightSystem->RegisterLight(_geLight);
}

void Engine::Component::Light::Detach()
{
	Component::Detach();
	auto lightSystem = _graphicsManager->GetLightSystem();
	lightSystem->UnRegisterLight(_geLight);
}

void Engine::Component::Light::Finalize()
{
	_geLight->Release();
}

void Engine::Component::Light::SetType(Type type) const
{
	_geLight->SetType(static_cast<GE::ILight::Type>(type));
}

void Engine::Component::Light::SetIntensity(const float intensity) const
{
	_geLight->SetIntensity(intensity);
}

void Engine::Component::Light::SetPosition(const float x, const float y, const float z) const
{
	_geLight->SetPosition(x, y, z);
}

void Engine::Component::Light::SetRange(const float range) const
{
	_geLight->SetRange(range);
}

void Engine::Component::Light::SetDirection(const float x, const float y, const float z) const
{
	_geLight->SetDirection(x, y, z);
}

void Engine::Component::Light::SetDiffuse(const float r, const float g, const float b, const float a) const
{
	_geLight->SetDiffuse(r, g, b, a);
}

void Engine::Component::Light::SetSpecular(const float r, const float g, const float b, const float a) const
{
	_geLight->SetSpecular(r, g, b, a);
}

void Engine::Component::Light::SetAmbient(const float r, const float g, const float b, const float a) const
{
	_geLight->SetAmbient(r, g, b, a);
}

void Engine::Component::Light::SetAttenuation(const float constant, const float linear, const float quadratic) const
{
	_geLight->SetAttenuation(constant, linear, quadratic);
}

void Engine::Component::Light::SetPositionFromArray(float* pArray) const
{
	_geLight->SetPositionFromArray(pArray);
}

void Engine::Component::Light::SetDirectionFromArray(float* pArray) const
{
	_geLight->SetDiffsueFromArray(pArray);
}

void Engine::Component::Light::SetDiffuseFromArray(float* pArray) const
{
	_geLight->SetDiffsueFromArray(pArray); // TODO: Fix this typo.
}

void Engine::Component::Light::SetSpecularFromArray(float* pArray)
{
	_geLight->SetSpecularFromArray(pArray);
}

void Engine::Component::Light::SetAmbientFromArray(float* pArray)
{
	_geLight->SetAmbientFromArray(pArray);
}

