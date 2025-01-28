#include "pch.h"
#include "GraphicsComponent.h"

Engine::Component::GraphicsComponent::GraphicsComponent():
_graphicsManager(nullptr)
{
}

void Engine::Component::GraphicsComponent::Initialize(const Modules& modules)
{
	Component::Initialize(modules);
	_graphicsManager = modules.graphicsManager;
}

