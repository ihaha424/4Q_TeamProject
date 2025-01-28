#include "pch.h"
#include "WorldFactory.h"

Engine::Content::Factory::World::World(Object* objectFactory, Engine::World** cloned):
	_objectFactory(objectFactory), _cloned(cloned)
{
}
