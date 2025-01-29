#include "pch.h"
#include "ComponentFactory.h"

Engine::Content::Factory::Component::Component(std::vector<Engine::Component::Component*>* cloned) :
	_cloned(cloned)
{
}
