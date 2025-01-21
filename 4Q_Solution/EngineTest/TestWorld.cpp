#include "pch.h"
#include "TestWorld.h"

void TestWorld::Addition()
{
	World::Addition();
	AddObject(&_player);
}