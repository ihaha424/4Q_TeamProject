#include "pch.h"
#include "ObjectFactory.h"

Engine::Content::Factory::Object::Object(Component* objectFactory, std::vector<Engine::Object*>* cloned) :
	_componentFactory(objectFactory), _cloned(cloned)
{
}
