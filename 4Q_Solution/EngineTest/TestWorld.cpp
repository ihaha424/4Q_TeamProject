#include "pch.h"
#include "TestWorld.h"
#include "NetworkTemp.h"



void TestWorld::Addition()
{
	World::Addition();
	AddObject(&_player);
	//AddObject(&_remote);
	AddObject(&_light);
	AddObject(&_terrain);

}

void TestWorld::PreInitialize()
{
	NetworkTemp::GetInstance()->AddCallback((short)PacketID::EnterAccept, &TestWorld::EnterAccept, this);
	NetworkTemp::GetInstance()->AddCallback((short)PacketID::Sync, &TestWorld::SyncOtherPlayer, this);
	
}

void TestWorld::PreUpdate(float deltaTime)
{
	//NetworkTemp::GetInstance()->Dispatch();
}

void TestWorld::PostFixedUpdate()
{
	//NetworkTemp::GetInstance()->SendUpdate();
}

void TestWorld::EnterAccept(const ConnectMsg::EnterAccept* msg)
{
	playerSerialNum = msg->grantnumber();
}

void TestWorld::SyncOtherPlayer(const ConnectMsg::SyncPlayer* msg)
{
	if (playerSerialNum == msg->serialnumber()) return;

	AddObject(&_remote);
}
