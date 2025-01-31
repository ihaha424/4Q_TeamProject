#include "pch.h"
#include "TestWorld.h"
#include "NetworkTemp.h"



void TestWorld::Prepare(Engine::Content::Factory::Object* objectFactory)
{
	//_player = Engine::Application::GetContentManager()->GetObjectFactory()->Clone<Player>();
	_player = objectFactory->Clone<Player>();
	_light = objectFactory->Clone<GlobalLight>();
	_terrain = objectFactory->Clone<Terrain>();
}

void TestWorld::PreInitialize(const Engine::Modules& modules)
{
	Engine::Application::GetNetworkManager()->RegistWorldEvent(
		(short)PacketID::EnterAccept,
		[this](int num) {
			EnterAccept(num);
		}
		);
	Engine::Application::GetNetworkManager()->RegistWorldEvent(
		(short)PacketID::Sync,
		[this](int num) {
			SyncOtherPlayer(num);
		}
	);
	Engine::Application::GetNetworkManager()->RegistWorldEvent(
		(short)PacketID::ObjectSync,
		[this](int num) {
			CreateStaticObject(num);
		}
	);
	Engine::Application::GetNetworkManager()->RegistWorldEvent(
		(short)PacketID::DataSendComplete,
		[this](int num) {
			RequestData(num);
		}
	);

	auto PhysicsManager = Engine::Application::GetPhysicsManager();
	Engine::Physics::SceneDesc testSceneDesc{ {0.f,-9.8f,0.f},10 };
	PhysicsManager->CreateScene(&mainScene, testSceneDesc);
	PhysicsManager->AttachUpdateScene(mainScene);
	PhysicsManager->CreateControllerManager(mainScene);

	Engine::Physics::SceneDesc cameraSceneDesc{ {0.f,0.f,0.f},0 };
	Engine::Application::GetPhysicsManager()->CreateCameraScene(&cameraScene, cameraSceneDesc);
	PhysicsManager->AttachUpdateScene(cameraScene);
}

void TestWorld::PreUpdate(float deltaTime)
{

}

void TestWorld::PostFixedUpdate()
{

}

void TestWorld::EnterAccept(int num) {
	
}

void TestWorld::SyncOtherPlayer(int num)
{
	_remote = Engine::Application::GetContentManager()->GetObjectFactory()->Clone<RemotePlayer>();
	_remote->SetSerialNumber(num);
}

void TestWorld::CreateStaticObject(int num)
{
	Cube* cube = Engine::Application::GetContentManager()->GetObjectFactory()->Clone<Cube>();
	_cubes.push_back(cube);
	cube->SetSerialNumber(num);
}

void TestWorld::RequestData(int num)
{
	if (_loadComplete == false) {
		std::string data = "";
		Engine::Application::GetNetworkManager()->SaveSendData((short)PacketID::DataRequest, data, 0, 0);
		_loadComplete = true;
	}
}
