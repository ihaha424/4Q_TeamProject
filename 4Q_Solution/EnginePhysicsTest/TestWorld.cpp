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
	//NetworkTemp::GetInstance()->AddCallback((short)PacketID::EnterAccept, &TestWorld::EnterAccept, this);
	//NetworkTemp::GetInstance()->AddCallback((short)PacketID::Sync, &TestWorld::SyncOtherPlayer, this);

	Engine::Physics::SceneDesc testSceneDesc{ {0.f,-9.8f,0.f},10 };
	Engine::Application::GetPhysicsManager()->CreateScene(&testPhysicsSecne, testSceneDesc);
	Engine::Application::GetPhysicsManager()->AttachUpdateSecne(testPhysicsSecne);

	Engine::Physics::IRigidComponent* obj;
	Engine::Application::GetPhysicsManager()->CreatePlane(&obj, Engine::Math::Vector4{ 0, 1, 0, -300 }, Engine::Physics::MaterialDesc{ {0.5f, 0.5f, 0.f} });
	testPhysicsSecne->AddActor(obj);
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
