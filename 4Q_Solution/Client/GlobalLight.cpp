#include "pch.h"
#include "GlobalLight.h"

const unsigned int maxLight = 5;

GlobalLight::GlobalLight()
	: _globalLight(nullptr)
{
}

void GlobalLight::Prepare(Engine::Content::Factory::Component* componentFactory)
{	
	_globalLight = componentFactory->Clone<Engine::Component::Light>(this);
	
	/*for (int i = 0; i < maxLight; i++)
		_pointLights.push_back(componentFactory->Clone<Engine::Component::Light>(this));*/
}

void GlobalLight::DisposeComponents()
{
	_globalLight->Dispose();

	for (auto& light : _pointLights)
		light->Dispose();
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

	/*for (int i = 0; i < maxLight; i++)
	{
		_pointLights[i]->SetType(Engine::Component::Light::Type::Point);
		_pointLights[i]->SetDiffuse(1.f, 1.f, 1.f, 1.f);
		_pointLights[i]->SetSpecular(1.f, 1.f, 1.f, 1.f);
		_pointLights[i]->SetAmbient(0.2f, 0.2f, 0.2f, 0.2f);
		_pointLights[i]->SetPosition(i * 100.f, 200.f, 0.f);
		_pointLights[i]->SetRange(500.f);
		_pointLights[i]->SetIntensity(0.1f + i * 3.f);
	}*/
}
