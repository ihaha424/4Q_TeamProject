#include "pch.h"
#include "TestWorld.h"


void TestWorld::Prepare(Engine::Content::Factory::Object* objectFactory)
{
	_player = objectFactory->Clone<Player>();
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