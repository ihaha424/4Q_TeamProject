#include "pch.h"
#include "SimpleCamera.h"

SimpleCamera::SimpleCamera()
{
}

void SimpleCamera::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_camera = componentFactory->Clone<Engine::Component::Camera>(this);
}

void SimpleCamera::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);

	_camera->SetName(L"SimpleCamera");
}

void SimpleCamera::PostAttach()
{
	Object::PostAttach();
	_camera->Activate();
}

void SimpleCamera::DisposeComponents()
{
	_camera->Dispose();
}
