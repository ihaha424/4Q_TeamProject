#include "pch.h"
#include "TestWorld.h"

void TestWorld::Prepare(Engine::Content::Factory::Object* objectFactory)
{
	_ray = objectFactory->Clone<Ray>(this);
	_light = objectFactory->Clone<GlobalLight>(this);
	_terrain = objectFactory->Clone<Terrain>(this);
	_skyBox = objectFactory->Clone<SkyBox>(this);
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