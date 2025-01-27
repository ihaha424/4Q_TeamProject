#include "pch.h"
#include "TestWorld.h"
#include "NetworkTemp.h"



void TestWorld::Addition()
{
	World::Addition();
	AddObject(&_player);
	AddObject(&_remote);
	AddObject(&_light);
	AddObject(&_terrain);

}

void TestWorld::PreInitialize()
{
	
}

void TestWorld::PreUpdate(float deltaTime)
{

}

void TestWorld::PostFixedUpdate()
{

}

void TestWorld::SyncOtherPlayer(const ConnectMsg::SyncPlayer* msg)
{
	if (playerSerialNum == msg->serialnumber()) return;

	//AddObject(&_remote);
	//_remote.Attach();
}
