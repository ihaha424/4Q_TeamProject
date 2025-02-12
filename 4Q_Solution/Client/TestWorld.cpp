#include "pch.h"
#include "TestWorld.h"

#include "Application.h"
#include "NPC_Hide.h"
#include "NPC_Ornoa.h"
#include "NPC_Ornoa_Elder.h"

void TestWorld::Prepare(Engine::Content::Factory::Object* objectFactory)
{
	//auto object = GameClient::Application::GetLoadManager()->GetObjectCloneData(L"BG_Ornoa_Cloth_2");
	//for (auto& data : object)
	//{
	//	auto building = objectFactory->Clone<BG_Ornoa_Cloth_2>(this);
	//	building->SetisDynamic(data.GetProperty<bool>(L"isDynamic").value());
	//	building->SetIsPublic(data.GetProperty<bool>(L"isPublic").value());
	//	building->SetHasMesh(data.GetProperty<bool>(L"hasMesh").value());
	//	building->SetTransform({
	//			data.GetProperty<Engine::Math::Vector3>(L"position").value(),
	//			data.GetProperty<Engine::Math::Quaternion>(L"rotation").value(),
	//			data.GetProperty<Engine::Math::Vector3>(L"scale").value() * 100.
	//		});
	//	building->SetBoxPosition({ data.GetProperty<Engine::Math::Vector3>(L"boxPosition").value() });
	//	building->SetBoxScale(data.GetProperty<Engine::Math::Vector3>(L"boxScale").value());
	//}

	//_ray = objectFactory->Clone<Ray>(this);
	_light = objectFactory->Clone<GlobalLight>(this);
	_skyBox = objectFactory->Clone<SkyBox>(this);
	//_testSprite = objectFactory->Clone<TestSprite>(this);

	// NPC
	{
		objectFactory->Clone<NPC_Hide>(this);
		objectFactory->Clone<NPC_Ornoa>(this);
		objectFactory->Clone<NPC_Ornoa_Elder>(this);
	}

	// BG_Terrain
	{
		objectFactory->Clone<BG_Terrain>(this);
		//helpPrepare<BG_Terrain>(L"BG_Terrain", objectFactory);
	}

	// Obj_Bermiore_Fabric
	{
		helpPrepare<Obj_Bermiore_Fabric>(L"Obj_Bermiore_Fabric", objectFactory);
	}

	// Obj_Bermiore_Hanger
	{
		helpPrepare<Obj_Bermiore_Hanger>(L"Obj_Bermiore_Hanger", objectFactory);
	}

	// Obj_Shinave_SteppedSudium
	{
		helpPrepare<Obj_Shinave_SteppedSudium>(L"Obj_Shinave_SteppedSudium", objectFactory);
	}

	// Obj_Ornoa_Print
	{
		helpPrepare<Obj_Ornoa_Print>(L"Obj_Ornoa_Print", objectFactory);
	}

	// BG_Ornoa_Cloth_3
	{
		helpPrepare<BG_Ornoa_Cloth_3>(L"BG_Ornoa_Cloth_3", objectFactory);
	}

	// BG_Ornoa_Cloth_2
	{
		helpPrepare<BG_Ornoa_Cloth_2>(L"BG_Ornoa_Cloth_2", objectFactory);
	}

	// BG_Ornoa_Cloth_1
	{
		helpPrepare<BG_Ornoa_Cloth_1>(L"BG_Ornoa_Cloth_1", objectFactory);
	}

	// Obj_BG_Tree_3
	{
		//helpPrepare<Obj_BG_Tree_3>(L"Obj_BG_Tree_3", objectFactory);
	}

	// Obj_BG_Tree_2
	{
		helpPrepare<Obj_BG_Tree_2>(L"Obj_BG_Tree_2", objectFactory);
	}

	// Obj_BG_Tree_1
	{
		helpPrepare<Obj_BG_Tree_1>(L"Obj_BG_Tree_1", objectFactory);
	}

	// Obj_Buildings_Ornoa_House_1
	{
		helpPrepare<Obj_Buildings_Ornoa_House_1>(L"Obj_Buildings_Ornoa_House_1", objectFactory);
	}

	// Obj_Buildings_Ornoa_House_2
	{
		helpPrepare<Obj_Buildings_Ornoa_House_2>(L"Obj_Buildings_Ornoa_House_2", objectFactory);
	}

	// BG_Props_Fence
	{
		helpPrepare<BG_Props_Fence>(L"BG_Props_Fence", objectFactory);
	}

	// Obj_Buildings_Sudium
	{
		helpPrepare<Obj_Buildings_Sudium>(L"Obj_Buildings_Sudium", objectFactory);
	}

	// Obj_Buildings_Hide_House_5
	{
		helpPrepare<Obj_Buildings_Hide_House_5>(L"Obj_Buildings_Hide_House_5", objectFactory);
	}

	// Obj_Buildings_Hide_House_4
	{
		helpPrepare<Obj_Buildings_Hide_House_4>(L"Obj_Buildings_Hide_House_4", objectFactory);
	}

	// Obj_Buildings_Hide_House_3
	{
		helpPrepare<Obj_Buildings_Hide_House_3>(L"Obj_Buildings_Hide_House_3", objectFactory);
	}

	// Obj_Buildings_Hide_House_2
	{
		helpPrepare<Obj_Buildings_Hide_House_2>(L"Obj_Buildings_Hide_House_2", objectFactory);
	}

	// Obj_Buildings_Hide_House_1
	{
		helpPrepare<Obj_Buildings_Hide_House_1>(L"Obj_Buildings_Hide_House_1", objectFactory);
	}

	// 	// Obj_Hide_Xylophone
	{
		// TODO: Hide_Xylophone
	}

	// Obj_Hide_Plant
	{
		// TODO: Hide_Plant
	}

	// Obj_Sudium_blue
	{
		helpPrepare<Obj_Sudium_blue>(L"Obj_Sudium_blue", objectFactory);
	}

	// Obj_Sudium_red
	{
		helpPrepare<Obj_Sudium_red>(L"Obj_Sudium_red", objectFactory);
	}

	// Obj_Mini_Platform_Set
	{
		// TODO: Refactor this.
		auto object = GameClient::Application::GetLoadManager()->GetObjectCloneData(L"Obj_Mini_Platform_Set");
		for (auto& data : object)
		{
			auto building = objectFactory->Clone<Obj_Mini_Platform_Set>(this);
			building->SetisDynamic(data.GetProperty<bool>(L"isDynamic").value());
			building->SetIsPublic(data.GetProperty<bool>(L"isPublic").value());
			building->SetHasMesh(data.GetProperty<bool>(L"hasMesh").value());
			building->SetTransform({
					data.GetProperty<Engine::Math::Vector3>(L"position").value(),
					data.GetProperty<Engine::Math::Quaternion>(L"rotation").value(),
					data.GetProperty<Engine::Math::Vector3>(L"scale").value() * 100.
				});
			building->SetBoxPosition({ data.GetProperty<Engine::Math::Vector3>(L"boxPosition").value() });
			building->SetBoxScale(data.GetProperty<Engine::Math::Vector3>(L"boxScale").value());
		}
		//helpPrepare<Obj_Mini_Platform_Set>(L"Obj_Mini_Platform_Set", objectFactory);
	}

	// Obj_Mini_Platform_Spawn
	{
		// TODO: Refactor this.
		auto object = GameClient::Application::GetLoadManager()->GetObjectCloneData(L"Obj_Mini_Platform_Spawn");
		for (auto& data : object)
		{
			auto building = objectFactory->Clone<Obj_Mini_Platform_Spawn>(this);
			building->SetisDynamic(data.GetProperty<bool>(L"isDynamic").value());
			building->SetIsPublic(data.GetProperty<bool>(L"isPublic").value());
			building->SetHasMesh(data.GetProperty<bool>(L"hasMesh").value());
			building->SetTransform({
					data.GetProperty<Engine::Math::Vector3>(L"position").value(),
					data.GetProperty<Engine::Math::Quaternion>(L"rotation").value(),
					data.GetProperty<Engine::Math::Vector3>(L"scale").value() * 100.
				});
			building->SetBoxPosition({ data.GetProperty<Engine::Math::Vector3>(L"boxPosition").value() });
			building->SetBoxScale(data.GetProperty<Engine::Math::Vector3>(L"boxScale").value());
		}
		//helpPrepare<Obj_Mini_Platform_Spawn>(L"Obj_Mini_Platform_Spawn", objectFactory);
	}

	// Obj_BG_Tree_3_Active
	{
		helpPrepare<Obj_BG_Tree_3_Active>(L"Obj_BG_Tree_3_Active", objectFactory);
	}

	// Obj_BG_Tree_1_Active
	{
		helpPrepare<Obj_BG_Tree_1_Active>(L"Obj_BG_Tree_1_Active", objectFactory);
	}

	// Obj_Shinave_Stone_1
	{
		helpPrepare<Obj_Shinave_Stone_1>(L"Obj_Shinave_Stone_1", objectFactory);
	}

	// Obj_Shinave_Stone_2
	{
		helpPrepare<Obj_Shinave_Stone_2>(L"Obj_Shinave_Stone_2", objectFactory);
	}

	// Obj_Shinave_Stone_3
	{
		helpPrepare<Obj_Shinave_Stone_3>(L"Obj_Shinave_Stone_3", objectFactory);
	}

	//	Obj_Shinave_Stone_4
	{
		helpPrepare<Obj_Shinave_Stone_4>(L"Obj_Shinave_Stone_4", objectFactory);
	}

	// Obj_Shinave_Stone_5
	{
		helpPrepare<Obj_Shinave_Stone_5>(L"Obj_Shinave_Stone_5", objectFactory);
	}

	// Obj_Shinave_Platform_Set
	{
		helpPrepare<Obj_Shinave_Platform_Set>(L"Obj_Shinave_Platform_Set", objectFactory);
	}

	// Obj_Shinave_Platform_Spawn_1
	{
		helpPrepare<Obj_Shinave_Platform_Spawn_1>(L"Obj_Shinave_Platform_Spawn_1", objectFactory);
	}

	// Obj_Shinave_Platform_Spawn_2
	{
		helpPrepare<Obj_Shinave_Platform_Spawn_2>(L"Obj_Shinave_Platform_Spawn_2", objectFactory);
	}

	// Obj_Shinave_Platform_Spawn_3
	{
		helpPrepare<Obj_Shinave_Platform_Spawn_3>(L"Obj_Shinave_Platform_Spawn_3", objectFactory);
	}

	// Obj_Props_Rock
	{
		helpPrepare<Obj_Props_Rock>(L"Obj_Props_Rock", objectFactory);
	}

	// Obj_Bermiore_Woolball_inBox
	{
		// TODO: Bermiore_Woolball_inBox
	}

	// TODO: Wool Series
	// TODO: Wool ball Series

	// Obj_Buildings_Bermiore_Atelier_1
	{
		helpPrepare<Obj_Buildings_Bermiore_Atelier_1>(L"Obj_Buildings_Bermiore_Atelier_1", objectFactory);
	}

	// Obj_Buildings_Bermiore_Atelier_2
	{
		helpPrepare<Obj_Buildings_Bermiore_Atelier_2>(L"Obj_Buildings_Bermiore_Atelier_2", objectFactory);
	}

	// Obj_Buildings_Bermiore_Atelier_3
	{
		helpPrepare<Obj_Buildings_Bermiore_Atelier_3>(L"Obj_Buildings_Bermiore_Atelier_3", objectFactory);
	}

	// Obj_Hide_Potion
	{
		// TODO: Refactor this.
		auto object = GameClient::Application::GetLoadManager()->GetObjectCloneData(L"Obj_Hide_Potion");
		for (auto& data : object)
		{
			auto building = objectFactory->Clone<Obj_Hide_Potion>(this);
			building->SetisDynamic(data.GetProperty<bool>(L"isDynamic").value());
			building->SetIsPublic(data.GetProperty<bool>(L"isPublic").value());
			building->SetHasMesh(data.GetProperty<bool>(L"hasMesh").value());
			building->SetTransform({
					data.GetProperty<Engine::Math::Vector3>(L"position").value(),
					data.GetProperty<Engine::Math::Quaternion>(L"rotation").value(),
					data.GetProperty<Engine::Math::Vector3>(L"scale").value() * 100.
				});
			building->SetBoxPosition({ data.GetProperty<Engine::Math::Vector3>(L"boxPosition").value() });
			building->SetBoxScale(data.GetProperty<Engine::Math::Vector3>(L"boxScale").value());
		}
		//helpPrepare<Obj_Hide_Potion>(L"Obj_Hide_Potion", objectFactory);
	}

	// Obj_Shinave_Bermiore
	{
		helpPrepare<Obj_Shinave_Bermiore>(L"Obj_Shinave_Bermiore", objectFactory);
	}

	// Obj_Bermiore_Soundblock
	{
		helpPrepare<Obj_Bermiore_Soundblock>(L"Obj_Bermiore_Soundblock", objectFactory);
	}

	// Obj_Mini_Stone_1
	{		
		helpPrepare<Obj_Mini_Stone_1>(L"Obj_Mini_Stone_1", objectFactory);
	}

	// Obj_Mini_Stone_2
	{
		helpPrepare<Obj_Mini_Stone_2>(L"Obj_Mini_Stone_2", objectFactory);
	}

	// Obj_Mini_Stone_3
	{
		helpPrepare<Obj_Mini_Stone_3>(L"Obj_Mini_Stone_3", objectFactory);
	}

	// Obj_Mini_Stone_4
	{
		helpPrepare<Obj_Mini_Stone_4>(L"Obj_Mini_Stone_4", objectFactory);
	}

	// Obj_Mini_Stone_5
	{
		helpPrepare<Obj_Mini_Stone_5>(L"Obj_Mini_Stone_5", objectFactory);
	}

	// Obj_Hide_Box
	{
		// TODO: Refactor this.
		auto object = GameClient::Application::GetLoadManager()->GetObjectCloneData(L"Obj_Hide_Box");
		for (auto& data : object)
		{
			auto building = objectFactory->Clone<Obj_Hide_Box>(this);
			building->SetisDynamic(data.GetProperty<bool>(L"isDynamic").value());
			building->SetIsPublic(data.GetProperty<bool>(L"isPublic").value());
			building->SetHasMesh(data.GetProperty<bool>(L"hasMesh").value());
			building->SetTransform({
					data.GetProperty<Engine::Math::Vector3>(L"position").value(),
					data.GetProperty<Engine::Math::Quaternion>(L"rotation").value(),
					data.GetProperty<Engine::Math::Vector3>(L"scale").value() * 100.
				});
			building->SetBoxPosition({ data.GetProperty<Engine::Math::Vector3>(L"boxPosition").value() });
			building->SetBoxScale(data.GetProperty<Engine::Math::Vector3>(L"boxScale").value());
		}
		//helpPrepare<Obj_Hide_Box>(L"Obj_Hide_Box", objectFactory);
	}

	// Obj_Ornoa_Soundblock_5
	{
		helpPrepare<Obj_Hide_Box>(L"Obj_Ornoa_Soundblock_5", objectFactory);
	}

	// Obj_Ornoa_Soundblock_4
	{
		helpPrepare<Obj_Ornoa_Soundblock_4>(L"Obj_Ornoa_Soundblock_4", objectFactory);
	}

	// Obj_Ornoa_Soundblock_3
	{
		helpPrepare<Obj_Ornoa_Soundblock_3>(L"Obj_Ornoa_Soundblock_3", objectFactory);
	}

	// Obj_Ornoa_Soundblock_2
	{
		helpPrepare<Obj_Ornoa_Soundblock_2>(L"Obj_Ornoa_Soundblock_2", objectFactory);
	}

	// Obj_Ornoa_Soundblock_1
	{
		helpPrepare<Obj_Ornoa_Soundblock_1>(L"Obj_Ornoa_Soundblock_1", objectFactory);
	}

	// Puzzle Manager
	{
		objectFactory->Clone<MainPuzzleManager>(this);
		objectFactory->Clone<PuzzleManager00>(this);
		objectFactory->Clone<PuzzleManager01>(this);
		objectFactory->Clone<PuzzleManager02>(this);
		objectFactory->Clone<PuzzleManager03>(this);
		objectFactory->Clone<PuzzleManager04>(this);
	}
}

void TestWorld::PreInitialize(const Engine::Modules& modules)
{
	//NetworkTemp::GetInstance()->AddCallback((short)PacketID::EnterAccept, &TestWorld::EnterAccept, this);
	//NetworkTemp::GetInstance()->AddCallback((short)PacketID::Sync, &TestWorld::SyncOtherPlayer, this);

	auto _physicsManager = Engine::Application::GetPhysicsManager();

	// 메인 씬 만들기 - 중력값 설정 필요
	Engine::Physics::SceneDesc mainSceneDesc{ {0.f, 0.f,0.f},0 };
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

	geometryDesc.data = { std::numbers::pi_v<float> / 4.f, 16.f / 9.f, 1.f, 1000.0f };
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
	Engine::Application::GetPhysicsManager()->UpdateScene(mainScene, deltaTime);
	Engine::Application::GetPhysicsManager()->FetchScene(mainScene, true);

	//Engine::Physics::AdditionalQueryData OverlapInfo;
	//// TODO: transform = GetCameraTransform 해서 넣어줘야함

	//auto* camera = _currentPlayer->GetCamera();
	//Engine::Math::Matrix matrix = camera->GetCameraMatrix();

	//Engine::Math::Vector3 position, scale; 
	//Engine::Math::Quaternion rotation;
	//matrix.Decompose(scale, rotation, position);

	//rotation = Engine::Math::Quaternion::CreateFromYawPitchRoll(std::numbers::pi_v< float> * 0.5f, std::numbers::pi_v < float>, 0.f) * rotation;
	//Engine::Transform transform{};
	//transform.rotation = rotation;
	//transform.position = position;
	//mainScene->Overlap(OverlapInfo, "Camera", transform);

	//for (auto& object : OverlapInfo.UserDatas)
	//{
	//	Engine::Object* owner = static_cast<Engine::Object*>(object->GetOwner());
	//	owner->Show();
	//}
}

void TestWorld::PostFixedUpdate()
{
}

void TestWorld::EnterAccept(const ConnectMsg::AddObject* msg) {
	if (msg->grantnumber() == 1) {
		_ray = Engine::Application::GetContentManager()->GetObjectFactory()->Clone<Ray>(this);
		playerSerialNum = msg->grantnumber();
		_ray->SetSerialNumber(msg->grantnumber());
		Engine::Application::GetGameStateManager()->RegisterData(L"GameCoreData", GameCoreData{ 3 });

		_currentPlayer = _ray;
	}
	else if (msg->grantnumber() == 2) {
		// TODO: 여기에 리브의 오브젝트를 생성하는 코드를 넣어야 합니다.
		_live = Engine::Application::GetContentManager()->GetObjectFactory()->Clone<Live>(this);
		playerSerialNum = msg->grantnumber();
		_live->SetSerialNumber(msg->grantnumber());
		Engine::Application::GetGameStateManager()->RegisterData(L"GameCoreData", GameCoreData{ 2 });

		_currentPlayer = _live;
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

	gameStateManager->RegisterData(L"GrabData", GrabData{});

	auto puzzle_00 = gameStateManager->NewSubManager();
	gameStateManager->RegisterSubManager(L"puzzle_00", puzzle_00);
	puzzle_00->RegisterData(L"Data", Puzzle_00{});

	auto puzzle_01 = gameStateManager->NewSubManager();
	gameStateManager->RegisterSubManager(L"puzzle_01", puzzle_01);
	puzzle_01->RegisterData(L"Data", Puzzle_01{});

	auto puzzle_02 = gameStateManager->NewSubManager();
	gameStateManager->RegisterSubManager(L"puzzle_02", puzzle_02);
	puzzle_02->RegisterData(L"Data", Puzzle_02{});

	auto puzzle_03 = gameStateManager->NewSubManager();
	gameStateManager->RegisterSubManager(L"puzzle_03", puzzle_03);
	puzzle_03->RegisterData(L"Data", Puzzle_03{});

	auto puzzle_04 = gameStateManager->NewSubManager();
	gameStateManager->RegisterSubManager(L"puzzle_04", puzzle_04);
	puzzle_04->RegisterData(L"Data", Puzzle_04{});

	auto puzzle_05 = gameStateManager->NewSubManager();
	gameStateManager->RegisterSubManager(L"puzzle_05", puzzle_05);
	puzzle_05->RegisterData(L"Data", Puzzle_05{});

}
