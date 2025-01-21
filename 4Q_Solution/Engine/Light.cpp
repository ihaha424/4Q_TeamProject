#include "pch.h"
#include "Light.h"
#include "GEGraphicsManager.h"

Engine::Component::Light::Light()
	: _geLight(nullptr)
{
}

void Engine::Component::Light::Initialize()
{
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

void Engine::Component::Light::SetType(Type type)
{
	_geLight->SetType(static_cast<GE::ILight::Type>(type));
}

void Engine::Component::Light::SetIntensity(float intensity)
{
	_geLight->SetIntensity(intensity);
}

void Engine::Component::Light::SetPosition(float x, float y, float z)
{
	_geLight->SetPosition(x, y, z);
}

void Engine::Component::Light::SetRange(float range)
{
	_geLight->SetRange(range);
}

void Engine::Component::Light::SetDirection(float x, float y, float z)
{
	_geLight->SetDirection(x, y, z);
}

void Engine::Component::Light::SetDiffuse(float r, float g, float b, float a)
{
	_geLight->SetDiffuse(r, g, b, a);
}

void Engine::Component::Light::SetSpecular(float r, float g, float b, float a)
{
	_geLight->SetSpecular(r, g, b, a);
}

void Engine::Component::Light::SetAmbient(float r, float g, float b, float a)
{
	_geLight->SetAmbient(r, g, b, a);
}

void Engine::Component::Light::SetAttenuation(float constant, float linear, float quadratic)
{
	_geLight->SetAttenuation(constant, linear, quadratic);
}

void Engine::Component::Light::SetPositionFromArray(float* pArray)
{
	_geLight->SetPositionFromArray(pArray);
}

void Engine::Component::Light::SetDirectionFromArray(float* pArray)
{
	_geLight->SetDiffsueFromArray(pArray);
}

void Engine::Component::Light::SetDiffsueFromArray(float* pArray)
{
	_geLight->SetDiffsueFromArray(pArray);
}

void Engine::Component::Light::SetSpecularFromArray(float* pArray)
{
	_geLight->SetSpecularFromArray(pArray);
}

void Engine::Component::Light::SetAmbientFromArray(float* pArray)
{
	_geLight->SetAmbientFromArray(pArray);
}

