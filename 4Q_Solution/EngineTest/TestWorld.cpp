#include "pch.h"
#include "TestWorld.h"

#include "GameApplication.h"
#include "NetworkTemp.h"

void TestWorld::Prepare(Engine::Content::Factory::Object* objectFactory)
{
	auto building1Data = GameApplication::GetLoadManager()->GetObjectCloneData(L"Building1");
	//for (auto& data : building1Data) 
	//{
	//	auto building = objectFactory->Clone<Buliding1>(this);
	//	building->SetPublic(data.GetProperty<bool>(L"isPublic").value());
	//	building->SetPosition(data.GetProperty<Engine::Math::Vector3>(L"position").value());
	//	building->SetRotation(data.GetProperty<Engine::Math::Quaternion>(L"rotation").value());
	//	building->SetScale(data.GetProperty<Engine::Math::Vector3>(L"scale").value());
	//}


	//_player = Engine::Application::GetContentManager()->GetObjectFactory()->Clone<Player>(this);
	_player = objectFactory->Clone<Player>(this);
	_light = objectFactory->Clone<GlobalLight>(this);
	_terrain = objectFactory->Clone<Terrain>(this);
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
	_player->SetSerialNumber(num);
}

void TestWorld::SyncOtherPlayer(int num)
{
	if (_player->GetSerialNumber() == num) {
		return;
	}
	_remote = Engine::Application::GetContentManager()->GetObjectFactory()->Clone<RemotePlayer>(this);
	_remote->SetSerialNumber(num);
}

void TestWorld::CreateStaticObject(int num)
{
	Cube* cube = Engine::Application::GetContentManager()->GetObjectFactory()->Clone<Cube>(this);
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
