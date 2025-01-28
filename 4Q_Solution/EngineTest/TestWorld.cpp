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
	
}

void TestWorld::PreUpdate(float deltaTime)
{

}

void TestWorld::PostFixedUpdate()
{

}

void TestWorld::SyncOtherPlayer(const ConnectMsg::SyncPlayer* msg)
{

	//AddObject(&_remote);
	//_remote.Attach();
}
