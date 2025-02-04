#include "pch.h"
#include "GlobalLight.h"

void GlobalLight::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_globalLight = componentFactory->Clone<Engine::Component::Light>();
	_pointLight = componentFactory->Clone<Engine::Component::Light>();
}

void GlobalLight::DisposeComponents()
{
	_globalLight->Dispose();
	_pointLight->Dispose();
}

void GlobalLight::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	_globalLight->SetType(Engine::Component::Light::Type::Directional);
	_globalLight->SetDiffuse(1.f, 1.f, 1.f, 1.f);
	_globalLight->SetSpecular(1.f, 1.f, 1.f, 1.f);
	_globalLight->SetAmbient(0.2f, 0.2f, 0.2f, 0.2f);
	_globalLight->SetDirection(0.f, 0.f, 1.f);
	_globalLight->SetIntensity(1.f);
	_globalLight->SetMainLight();
	/*_pointLight.SetType(Engine::Component::Light::Type::Point);
	_pointLight.SetDiffuse(1.f, 1.f, 1.f, 1.f);
	_pointLight.SetSpecular(1.f, 1.f, 1.f, 1.f);
	_pointLight.SetAmbient(0.2f, 0.2f, 0.2f, 0.2f);
	_pointLight.SetPosition(0.f, 0.f, 0.f);
	_pointLight.SetRange(1000.f);
	_pointLight.SetIntensity(1.f);*/
}
