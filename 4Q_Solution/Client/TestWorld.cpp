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
	
	auto _physicsManager = Engine::Application::GetPhysicsManager();

	// 메인 씬 만들기 - 중력값 설정 필요
	Engine::Physics::SceneDesc mainSceneDesc{ {0.f,-9.8f,0.f},0 };
	_physicsManager->CreateScene(&mainScene, mainSceneDesc);
	_physicsManager->AttachUpdateScene(mainScene);
	_physicsManager->CreateControllerManager(mainScene);

	// 카메라 씬 만들기 - 중력값X
	Engine::Physics::SceneDesc cameraSceneDesc{ {0.f,0.f,0.f},0 };
	_physicsManager->CreateCameraScene(&cameraScene, cameraSceneDesc);
	_physicsManager->AttachUpdateScene(cameraScene);


	// TODO: 카메라의 크기가 바뀌지 않는 다는 가정하에(1차 컬링 할 크기 기준)
	Engine::Physics::GeometryDesc geometryDesc;
	geometryDesc.type = Engine::Physics::GeometryShape::Frustum;
	//	Frustum data는 카메라 데이터
	//	data.x : fovY
	//	data.y : aspect
	//	data.z : nearPlane
	//	data.w : farPlane
	geometryDesc.data = { 120.f, 2, 0.01f, 10000.0f };
	_physicsManager->AddGeomtry("Camera", geometryDesc, {});


	
}

void TestWorld::PreUpdate(float deltaTime)
{
	//NetworkTemp::GetInstance()->Dispatch();
	//NetworkTemp::GetInstance()->SendUpdate();
}

void TestWorld::PostUpdate(float deltaTime)
{
	//Engine::Application::GetPhysicsManager()->UpdateScene(cameraScene, deltaTime);
	//Engine::Application::GetPhysicsManager()->FetchScene(cameraScene, true);

	Engine::Physics::AdditionalQueryData OverlapInfo;
	// TODO: transform = GetCameraTransform 해서 넣어줘야함
	Engine::Transform transform{};
	cameraScene->Overlap(OverlapInfo, "Camera", transform);

	for (auto& object : OverlapInfo.UserDatas)
	{
		static_cast<Engine::Object*>(object->GetOwner());
		// TODO:: RenderFlag 끄기
	}
}

void TestWorld::PostFixedUpdate()
{

}