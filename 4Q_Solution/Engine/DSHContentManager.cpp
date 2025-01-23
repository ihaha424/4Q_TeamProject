#include "pch.h"
#include "DSHContentManager.h"

void Engine::DSHContent::Manager::Finalize()
{
	// TODO: Implement this function.
}

Engine::Content::Factory<Engine::World>& Engine::DSHContent::Manager::GetWorldFactory()
{
	return _worldFactory;
}

Engine::Content::Factory<Engine::Object>& Engine::DSHContent::Manager::GetObjectFactory()
{
	return _objectFactory;
}

Engine::Content::Factory<Engine::Component::Component>& Engine::DSHContent::Manager::GetComponentFactory()
{
	return _componentFactory;
}
