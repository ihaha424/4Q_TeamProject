#include "pch.h"
#include "Object.h"

void Engine::Object::Initialize()
{
	std::ranges::for_each(_components, [](Component::Component* component) { component->Initialize(); });
}

void Engine::Object::Attach()
{
	std::ranges::for_each(_components, [](Component::Component* component) { component->Attach(); });
}

void Engine::Object::Update(float deltaTime)
{
	std::ranges::for_each(_components, [deltaTime](Component::Component* component) { component->Update(deltaTime); });
}

void Engine::Object::FixedUpdate()
{
	std::ranges::for_each(_components, [](Component::Component* component) { component->FixedUpdate(); });
}

void Engine::Object::Detach()
{
	std::ranges::for_each(_components, [](Component::Component* component) { component->Detach(); });
}

void Engine::Object::Finalize()
{
	std::ranges::for_each(_components, [](Component::Component* component) { component->Finalize(); });
}
