#include "pch.h"
#include "TestWorld.h"

#include "Application.h"


void TestWorld::Prepare(Engine::Content::Factory::Object* objectFactory)
{
	//_ray = objectFactory->Clone<Ray>(this);
	_light = objectFactory->Clone<GlobalLight>(this);
	_skyBox = objectFactory->Clone<SkyBox>(this);
	_testSprite = objectFactory->Clone<TestSprite>(this);

	//Test Grabbed Object Code -> Make and Load File Data
	{
		GrabbedObject* building = objectFactory->Clone<GrabbedObject>(this);
		Engine::Transform tempTransform{};
		tempTransform.position = { 200.f, 0.f, 0 };
		building->SetTransform(tempTransform);
		building->SetBoxScale({ 100, 500, 100 });
	}

	//Test Trigger Area Code -> Make and Load File Data
	{
		TriggerArea* puzzle = objectFactory->Clone<TriggerArea>(this);
		Engine::Transform tempTransform{};
		tempTransform.position = { 0.f, 0.f, 200.f };
		puzzle->SetTransform(tempTransform);
		puzzle->SetBoxScale({ 100, 100, 100 });
	}

	//Test Puzzle_00 Object Code -> Load File Data
	{
		Obj_Puzzle_Shinave_Stone_1* puzzle = objectFactory->Clone<Obj_Puzzle_Shinave_Stone_1>(this);
		Engine::Transform tempTransform{};
		tempTransform.position = { -200.f, 0.f, 0 };
		puzzle->SetTransform(tempTransform);
		puzzle->SetBoxScale({ 100, 100, 100 });
	}

	helpPrepare<Terrain>(L"Terrain", objectFactory);

	//helpPrepare<Obj_BG_Tree_1>(L"Obj_BG_Tree_1", objectFactory);
	// helpPrepare<Obj_BG_Tree_2>(L"Obj_BG_Tree_2", objectFactory);
	// helpPrepare<Obj_BG_Mountain>(L"Obj_BG_Mountain", objectFactory);

	helpPrepare<Obj_Props_Fence>(L"Obj_Props_Fence", objectFactory);

	helpPrepare<Obj_Buildings_Shinave>(L"Obj_Buildings_Shinave", objectFactory);
	// helpPrepare<Obj_Buildings_Bermiore_Atelier_1>(L"Obj_Buildings_Bermiore_Atelier_1", objectFactory);
	// helpPrepare<Obj_Buildings_Bermiore_Atelier_2>(L"Obj_Buildings_Bermiore_Atelier_2", objectFactory);
	// helpPrepare<Obj_Buildings_Bermiore_Atelier_3>(L"Obj_Buildings_Bermiore_Atelier_3", objectFactory);

	// helpPrepare<Obj_Props_Bermiore_Loom_1>(L"Obj_Props_Bermiore_Loom_1", objectFactory);
	// helpPrepare<Obj_Props_Bermiore_Loom_2>(L"Obj_Props_Bermiore_Loom_2", objectFactory);
	// helpPrepare<Obj_Props_Bermiore_Cloth_1>(L"Obj_Props_Bermiore_Cloth_1", objectFactory);
	// helpPrepare<Obj_Props_Bermiore_Cloth_2>(L"Obj_Props_Bermiore_Cloth_2", objectFactory);

	// helpPrepare<Obj_Buildings_Sudium>(L"Obj_Buildings_Sudium", objectFactory);

	helpPrepare<Obj_Buildings_Hide_House_1>(L"Obj_Buildings_Hide_House_1", objectFactory);
	helpPrepare<Obj_Buildings_Hide_House_2>(L"Obj_Buildings_Hide_House_2", objectFactory);
	helpPrepare<Obj_Buildings_Hide_House_3>(L"Obj_Buildings_Hide_House_3", objectFactory);
	helpPrepare<Obj_Buildings_Hide_House_4>(L"Obj_Buildings_Hide_House_4", objectFactory);

	helpPrepare<Obj_Buildings_Ornoa_House_1>(L"Obj_Buildings_Ornoa_House_1", objectFactory);
	helpPrepare<Obj_Buildings_Ornoa_House_2>(L"Obj_Buildings_Ornoa_House_2", objectFactory);
	// helpPrepare<Obj_Buildings_Ornoa_House_3>(L"Obj_Buildings_Ornoa_House_3", objectFactory);
	// helpPrepare<Obj_Buildings_Ornoa_House_4>(L"Obj_Buildings_Ornoa_House_4", objectFactory);
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


	Engine::Application::GetNetworkManager()->RegistWorldEvent(
		(short)PacketID::EnterAccept,
		[this](const ConnectMsg::AddObject* msg) {
			EnterAccept(msg);
		}
	);
	Engine::Application::GetNetworkManager()->RegistWorldEvent(
		(short)PacketID::Sync,
		[this](const ConnectMsg::AddObject* msg) {
			CreatePlayer(msg);
		}
	);
	Engine::Application::GetNetworkManager()->RegistWorldEvent(
		(short)PacketID::ObjectSync,
		[this](const ConnectMsg::AddObject* msg) {
			CreateStaticObject(msg);
		}
	);
	Engine::Application::GetNetworkManager()->RegistWorldEvent(
		(short)PacketID::DataSendComplete,
		[this](const ConnectMsg::AddObject* msg) {
			RequestData(msg);
		}
	);


	InitializeGameStateManager(modules);
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


void TestWorld::EnterAccept(const ConnectMsg::AddObject* msg) {
	if (msg->grantnumber() == 1) {
		_ray = Engine::Application::GetContentManager()->GetObjectFactory()->Clone<Ray>(this);
		playerSerialNum = msg->grantnumber();
		_ray->SetSerialNumber(msg->grantnumber());
	}
	else if (msg->grantnumber() == 2) {
		// TODO: 여기에 리브의 오브젝트를 생성하는 코드를 넣어야 합니다.
		_live = Engine::Application::GetContentManager()->GetObjectFactory()->Clone<Live>(this);
		playerSerialNum = msg->grantnumber();
		_live->SetSerialNumber(msg->grantnumber());
	}
}
void TestWorld::CreatePlayer(const ConnectMsg::AddObject* msg) {
	if (playerSerialNum == msg->grantnumber()) {
		return;
	}
	if (msg->grantnumber() == 1) {
		_remoteRay = Engine::Application::GetContentManager()->GetObjectFactory()->Clone<RemoteRay>(this);
		_remoteRay->SetSerialNumber(msg->grantnumber());
	}
	else if (msg->grantnumber() == 2) {
		// TODO: 여기에 리브의 오브젝트를 생성하는 코드를 넣어야 합니다.
		_remoteLive = Engine::Application::GetContentManager()->GetObjectFactory()->Clone<RemoteLive>(this);
		_remoteLive->SetSerialNumber(msg->grantnumber());
	}
}
void TestWorld::CreateStaticObject(const ConnectMsg::AddObject* msg) {
	
}
void TestWorld::RequestData(const ConnectMsg::AddObject* msg) {
	if (_dataLoad == false) {
		std::string data = "";
		Engine::Application::GetNetworkManager()->SaveSendData((short)PacketID::DataRequest, data, 0, 0);
		_dataLoad = true;
	}
}

void TestWorld::InitializeGameStateManager(const Engine::Modules& modules)
{
	auto gameStateManager = modules.gameStateManager;

	auto puzzle_00 = gameStateManager->NewSubManager();
	gameStateManager->RegisterSubManager(L"puzzle_00", puzzle_00);
	puzzle_00->RegisterData(L"Data", Puzzle_00{});

	auto puzzle_01 = gameStateManager->NewSubManager();
	gameStateManager->RegisterSubManager(L"puzzle_01", puzzle_01);
	puzzle_01->RegisterData(L"Data", Puzzle_01{});

	auto puzzle_02 = gameStateManager->NewSubManager();
	gameStateManager->RegisterSubManager(L"puzzle_02", puzzle_02);
	puzzle_02->RegisterData(L"Data", Puzzle_02{});

	auto puzzle_mini = gameStateManager->NewSubManager();
	gameStateManager->RegisterSubManager(L"puzzle_mini", puzzle_mini);
	puzzle_mini->RegisterData(L"Data", Puzzle_Mini{});

	auto puzzle_03 = gameStateManager->NewSubManager();
	gameStateManager->RegisterSubManager(L"puzzle_03", puzzle_03);
	puzzle_03->RegisterData(L"Data", Puzzle_03{});

	auto puzzle_04 = gameStateManager->NewSubManager();
	gameStateManager->RegisterSubManager(L"puzzle_04", puzzle_04);
	puzzle_04->RegisterData(L"Data", Puzzle_04{});

}
