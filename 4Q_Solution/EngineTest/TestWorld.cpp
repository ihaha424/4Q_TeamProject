#include "pch.h"
#include "TestWorld.h"
#include "NetworkTemp.h"



void TestWorld::Prepare(Engine::Content::Factory::Object* objectFactory)
{
	_player = objectFactory->Clone<Player>();
	_remote = objectFactory->Clone<RemotePlayer>();
	_light = objectFactory->Clone<GlobalLight>();
	_terrain = objectFactory->Clone<Terrain>();
}

void TestWorld::PreInitialize(const Engine::Modules& modules)
{
    //NetworkTemp::GetInstance()->AddCallback((short)PacketID::EnterAccept, &TestWorld::EnterAccept, this);
    //NetworkTemp::GetInstance()->AddCallback((short)PacketID::Sync, &TestWorld::SyncOtherPlayer, this);
	
}

void TestWorld::PreUpdate(float deltaTime)
{
	//NetworkTemp::GetInstance()->Dispatch();
	//NetworkTemp::GetInstance()->SendUpdate();
}

void TestWorld::PostFixedUpdate()
{

}

void TestWorld::EnterAccept(const ConnectMsg::EnterAccept* msg)
{
	playerSerialNum = msg->grantnumber();
}

void TestWorld::SyncOtherPlayer(const ConnectMsg::SyncPlayer* msg)
{
	if (playerSerialNum == msg->serialnumber()) return;

	//AddObject(&_remote);
	//_remote.Attach();
}
