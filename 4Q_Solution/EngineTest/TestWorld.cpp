#include "pch.h"
#include "TestWorld.h"

void TestWorld::Prepare(Engine::Content::Factory::Object* objectFactory)
{
	_player = objectFactory->Clone<Player>();
	_remote = objectFactory->Clone<RemotePlayer>();
	_light = objectFactory->Clone<GlobalLight>();
	_terrain = objectFactory->Clone<Terrain>();
}