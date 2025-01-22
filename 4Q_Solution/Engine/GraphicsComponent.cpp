#include "pch.h"
#include "GraphicsComponent.h"
#include "GEGraphicsManager.h"

Engine::Component::GraphicsComponent::GraphicsComponent()
	: _graphicsManager(nullptr)
{
}

void Engine::Component::GraphicsComponent::Setup(Modules modules)
{
	Component::Setup(modules);
	_graphicsManager = modules.graphicsManager;
}