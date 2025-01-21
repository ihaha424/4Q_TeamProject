#include "pch.h"
#include "TestWorld.h"

void TestWorld::PreInitialize()
{
	World::PreInitialize();
	AddObject(&_player);
}
