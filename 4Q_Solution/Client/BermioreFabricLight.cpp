#include "pch.h"
#include "BermioreFabricLight.h"

BermioreFabricLight::BermioreFabricLight()
	: _light(nullptr)
{
}

void BermioreFabricLight::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	for (int i = 0; i < 6; i++)
	{
		_light[i] = componentFactory->Clone<Engine::Component::Light>(this);
	}
}

void BermioreFabricLight::DisposeComponents()
{
	for (int i = 0; i < 6; i++)
	{
		_light[i]->Dispose();
	}
}

void BermioreFabricLight::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);		
}

void BermioreFabricLight::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);

	for (int i = 0; i < 6; i++)
	{
		_light[i]->SetType(Engine::Component::Light::Type::Point);
		_light[i]->SetDiffuse(0.f, 0.7f, 1.f, 1.f);
		_light[i]->SetSpecular(1.f, 1.f, 1.f, 1.f);
		_light[i]->SetRange(20.f);
		_light[i]->SetIntensity(10.f);
	}
	
	_light[0]->SetPosition(-1139.9f, 26.9f, -763.7f);
	_light[0]->SetDiffuse(0.f, 0.7f, 1.f, 1.f);

	_light[1]->SetPosition(-1137.5f, 13.7f, -752.4f);
	_light[1]->SetDiffuse(10.f, 0.7f, 1.f, 1.f);

	_light[2]->SetPosition(-1134.6f, 13.7f, -741.1f);
	_light[2]->SetDiffuse(0.f, 10.7f, 1.f, 1.f);

	_light[3]->SetPosition(-1133.2f, 20.7f, -729.4f);
	_light[3]->SetDiffuse(0.f, 0.7f, 11.f, 1.f);

	_light[4]->SetPosition(-1128.7f, 26.9f, -717.9f);
	_light[4]->SetDiffuse(10.f, 0.7f, 1.f, 1.f);

	_light[5]->SetPosition(-1124.1f, 13.f, -706.1f);
	_light[5]->SetDiffuse(0.f, 10.7f, 1.f, 1.f);
}

void BermioreFabricLight::PostUpdate(float deltaTime)
{
	Object::PostUpdate(deltaTime);
}