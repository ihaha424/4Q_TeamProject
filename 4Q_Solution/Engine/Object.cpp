#include "pch.h"
#include "Object.h"
#include "PHIObject.h"

void Engine::Object::Setup(Modules modules)
{
	Addition();
	std::ranges::for_each(_components, [modules](Component::Component* component) { component->Setup(modules); });
}

void Engine::Object::Initialize()
{
	PreInitialize();
	std::ranges::for_each(_components, [](Component::Component* component) { component->Initialize(); });
	PostInitialize();
}

void Engine::Object::Attach()
{
	PreAttach();
	std::ranges::for_each(_components, [](Component::Component* component) { component->Attach(); });
	PostAttach();
}

void Engine::Object::Update(float deltaTime)
{
	PreUpdate(deltaTime);
	std::ranges::for_each(_components, [deltaTime](Component::Component* component) { component->Update(deltaTime); });
	PostUpdate(deltaTime);
}

void Engine::Object::FixedUpdate()
{
	PreFixedUpdate();
	std::ranges::for_each(_components, [](Component::Component* component) { component->FixedUpdate(); });
	PostFixedUpdate();
}

void Engine::Object::Detach()
{
	PreDetach();
	std::ranges::for_each(_components, [](Component::Component* component) { component->Detach(); });
	PostDetach();
}

void Engine::Object::Finalize()
{
	PreFinalize();
	std::ranges::for_each(_components, [](Component::Component* component) { component->Finalize(); });
	PostFinalize();
}

void Engine::Object::Addition()
{
}

void Engine::Object::PreInitialize()
{
}

void Engine::Object::PostInitialize()
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

void Engine::Object::AddComponent(Component::Component* component)
{
	_components.push_back(component);
}
