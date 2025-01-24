#include "pch.h"
#include "TestWorld.h"

TestWorld::TestWorld(std::wstring argument1, int argument2)
{
	// Nothing to do
}

void TestWorld::Addition()
{
	World::Addition();
	AddObject(&_player);
	AddObject(&_remote);
	AddObject(&_light);
	AddObject(&_terrain);
}
