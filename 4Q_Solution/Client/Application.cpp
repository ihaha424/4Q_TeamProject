#include "pch.h"
#include "Application.h"

#include "TestWorld.h"

GameClient::Application::Application(const HINSTANCE instanceHandle) : Engine::Application(instanceHandle)
{
}

void GameClient::Application::LoadData(Engine::Load::IManager* loadManager)
{
	loadManager->LoadRegisterData(L"Assets/Test/MapData.json");
	loadManager->LoadCloneData(L"Assets/Test/MapData.json");
}

void GameClient::Application::DeclareInputActions(Engine::Input::IManager* inputManager)
{
	Engine::Input::IMappingContext* mappingContext = nullptr;
	inputManager->GetMappingContext(L"Default", &mappingContext);

	DeclareMoveAction(inputManager, mappingContext);
	DeclareCameraAction(inputManager, mappingContext);
	DeclareSystemAction(inputManager, mappingContext);

	inputManager->SetActiveMappingContext(mappingContext);
}

void GameClient::Application::Register(Engine::Content::IManager* contentManager, Engine::Load::IManager* loadManager)
{
	Engine::Application::Register(contentManager, loadManager);

	const auto worldFactory = contentManager->GetWorldFactory();
	worldFactory->Register<TestWorld>();

	const auto objectFactory = contentManager->GetObjectFactory();
	objectFactory->Register<GlobalLight>();
	objectFactory->Register<Ray>(L"Assets/Models/Ray.fbx");
	objectFactory->Register<RemoteRay>(L"Assets/Models/Ray.fbx");
	objectFactory->Register<Live>(L"Assets/Models/Live.fbx");
	objectFactory->Register<RemoteLive>(L"Assets/Models/Live.fbx");
	objectFactory->Register<SkyBox>(L"Assets/Models/skybox.fbx");

	// BG_Terrain
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"BG_Terrain").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<BG_Terrain>(buildingProperty, buildingProperty);
	}

	// Obj_Bermiore_Fabric
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Bermiore_Fabric").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Bermiore_Fabric>(buildingProperty, buildingProperty);
	}

	// Obj_Bermiore_Hanger
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Bermiore_Hanger").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Bermiore_Hanger>(buildingProperty, buildingProperty);
	}

	// Obj_Shinave_SteppedSudium
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Shinave_SteppedSudium").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Shinave_SteppedSudium>(buildingProperty, buildingProperty);
	}

	// Obj_Ornoa_Print
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Ornoa_Print").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Ornoa_Print>(buildingProperty, buildingProperty);
	}

	// BG_Ornoa_Cloth_3
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"BG_Ornoa_Cloth_3").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<BG_Ornoa_Cloth_3>(buildingProperty, buildingProperty);
	}

	// BG_Ornoa_Cloth_2
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"BG_Ornoa_Cloth_2").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<BG_Ornoa_Cloth_2>(buildingProperty, buildingProperty);
	}

	// BG_Ornoa_Cloth_1
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"BG_Ornoa_Cloth_1").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<BG_Ornoa_Cloth_1>(buildingProperty, buildingProperty);
	}

	// Obj_BG_Tree_3
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_BG_Tree_3").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_BG_Tree_3>(buildingProperty, buildingProperty);
	}

	// Obj_BG_Tree_2
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_BG_Tree_2").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_BG_Tree_2>(buildingProperty, buildingProperty);
	}

	// Obj_BG_Tree_1
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_BG_Tree_1").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_BG_Tree_1>(buildingProperty, buildingProperty);
	}

	// Obj_Buildings_Ornoa_House_1
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Buildings_Ornoa_House_1").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Buildings_Ornoa_House_1>(buildingProperty, buildingProperty);
	}

	// Obj_Buildings_Ornoa_House_2
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Buildings_Ornoa_House_2").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Buildings_Ornoa_House_2>(buildingProperty, buildingProperty);
	}

	// BG_Props_Fence
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"BG_Props_Fence").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<BG_Props_Fence>(buildingProperty, buildingProperty);
	}

	// Obj_Buildings_Sudium
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Buildings_Sudium").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Buildings_Sudium>(buildingProperty, buildingProperty);
	}

	// Obj_Buildings_Hide_House_5
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Buildings_Hide_House_5").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Buildings_Hide_House_5>(buildingProperty, buildingProperty);
	}

	// Obj_Buildings_Hide_House_4
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Buildings_Hide_House_4").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Buildings_Hide_House_4>(buildingProperty, buildingProperty);
	}

	// Obj_Buildings_Hide_House_3
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Buildings_Hide_House_3").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Buildings_Hide_House_3>(buildingProperty, buildingProperty);
	}

	// Obj_Buildings_Hide_House_2
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Buildings_Hide_House_2").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Buildings_Hide_House_2>(buildingProperty, buildingProperty);
	}

	// Obj_Buildings_Hide_House_1
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Buildings_Hide_House_1").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Buildings_Hide_House_1>(buildingProperty, buildingProperty);
	}

	// Obj_Hide_Xylophone
	{
		// TODO: Hide_Xylophone
	}

	// Obj_Hide_Plant
	{
		// TODO: Hide_Plant
	}

	// Obj_Sudium_blue
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Sudium_blue").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Sudium_blue>(buildingProperty, buildingProperty);
	}

	// Obj_Sudium_red
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Sudium_red").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Sudium_red>(buildingProperty, buildingProperty);
	}

	// Obj_Mini_Platform_Set
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Mini_Platform_Set").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Mini_Platform_Set>(buildingProperty, buildingProperty);
	}

	// Obj_Mini_Platform_Spawn
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Mini_Platform_Spawn").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Mini_Platform_Spawn>(buildingProperty, buildingProperty);
	}

	// Obj_BG_Tree_3_Active
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_BG_Tree_3_Active").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_BG_Tree_3_Active>(buildingProperty, buildingProperty);
	}

	// Obj_BG_Tree_1_Active
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_BG_Tree_1_Active").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_BG_Tree_1_Active>(buildingProperty, buildingProperty);
	}

	// Obj_Shinave_Stone_1
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Shinave_Stone_1").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Shinave_Stone_1>(buildingProperty, buildingProperty);
	}

	// Obj_Shinave_Stone_2
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Shinave_Stone_2").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Shinave_Stone_2>(buildingProperty, buildingProperty);
	}

	// Obj_Shinave_Stone_3
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Shinave_Stone_3").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Shinave_Stone_3>(buildingProperty, buildingProperty);
	}

	// Obj_Shinave_Stone_4
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Shinave_Stone_4").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Shinave_Stone_4>(buildingProperty, buildingProperty);
	}

	// Obj_Shinave_Stone_5
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Shinave_Stone_5").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Shinave_Stone_5>(buildingProperty, buildingProperty);
	}

	// Obj_Shinave_Platform_Set
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Shinave_Platform_Set").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Shinave_Platform_Set>(buildingProperty, buildingProperty);
	}

	// Obj_Shinave_Platform_Spawn_1
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Shinave_Platform_Spawn_1").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Shinave_Platform_Spawn_1>(buildingProperty, buildingProperty);
	}

	// Obj_Shinave_Platform_Spawn_2
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Shinave_Platform_Spawn_2").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Shinave_Platform_Spawn_2>(buildingProperty, buildingProperty);
	}

	// Obj_Shinave_Platform_Spawn_3
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Shinave_Platform_Spawn_3").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Shinave_Platform_Spawn_3>(buildingProperty, buildingProperty);
	}

	// Obj_Props_Rock
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Props_Rock").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Props_Rock>(buildingProperty, buildingProperty);
	}

	// Obj_Bermiore_Woolball_inBox
	{
		// TODO: Bermiore_Woolball_inBox
	}

	// TODO: Wool Series
	// TODO: Wool ball Series

	// Obj_Buildings_Bermiore_Atelier_1
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Buildings_Bermiore_Atelier_1").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Buildings_Bermiore_Atelier_1>(buildingProperty, buildingProperty);
	}

	// Obj_Buildings_Bermiore_Atelier_2
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Buildings_Bermiore_Atelier_2").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Buildings_Bermiore_Atelier_2>(buildingProperty, buildingProperty);
	}

	// Obj_Buildings_Bermiore_Atelier_3
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Buildings_Bermiore_Atelier_3").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Buildings_Bermiore_Atelier_3>(buildingProperty, buildingProperty);
	}

	// Obj_Hide_Potion
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Hide_Potion").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Hide_Potion>(buildingProperty, buildingProperty);
	}

	// Obj_Shinave_Bermiore
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Shinave_Bermiore").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Shinave_Bermiore>(buildingProperty, buildingProperty);
	}

	// Obj_Bermiore_Soundblock
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Bermiore_Soundblock").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Bermiore_Soundblock>(buildingProperty, buildingProperty);
	}

	// Obj_Mini_Stone_1
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Mini_Stone_1").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Mini_Stone_1>(buildingProperty, buildingProperty);
	}

	// Obj_Mini_Stone_2
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Mini_Stone_2").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Mini_Stone_2>(buildingProperty, buildingProperty);
	}

	// Obj_Mini_Stone_3
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Mini_Stone_3").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Mini_Stone_3>(buildingProperty, buildingProperty);
	}

	// Obj_Mini_Stone_4
	{
		auto buildingConfig = loadManager->GetObjectRegisterData(L"Obj_Mini_Stone_4").value();
		auto buildingProperty = buildingConfig.GetProperty<std::filesystem::path>(L"fbxPath").value();
		objectFactory->Register<Obj_Mini_Stone_4>(buildingProperty, buildingProperty);
	}




	//Test
	{
		//objectFactory->Register<GrabbedObject>("Assets/Test/cube.fbx", L"Assets/Test/cube.fbx");
		//objectFactory->Register<TriggerArea>("Assets/Test/cube.fbx", L"Assets/Test/cube.fbx");
		//objectFactory->Register<TestSprite>();
	}

	//RegisterHelp<Obj_Props_Bermiore_Loom_1>(L"Obj_Props_Bermiore_Loom_1", loadManager, objectFactory);
	//RegisterHelp<Obj_Props_Bermiore_Loom_2>(L"Obj_Props_Bermiore_Loom_2", loadManager, objectFactory);

	// Components
	{
		const auto componentFactory = contentManager->GetComponentFactory();
		componentFactory->Register<RemoteMove>();
		componentFactory->Register<TriggerBox>();
	}
}

void GameClient::Application::PrepareInitialWorld(Engine::Content::Factory::World* worldFactory)
{
	worldFactory->Clone<TestWorld>();
}

void GameClient::Application::DeclareMoveAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext)
{
	Engine::Input::Modifier::INegative* negative = nullptr;
	inputManager->GetModifier(&negative);
	Engine::Input::Modifier::ISwizzleAxis* swizzleAxis = nullptr;
	inputManager->GetModifier(Engine::Input::Modifier::ISwizzleAxis::Type::ZXY, &swizzleAxis);

	Engine::Input::Device::IKeyboard* keyboard = nullptr;
	inputManager->GetDevice(&keyboard);

	Engine::Input::Device::IController* controller = nullptr;
	inputManager->GetDevice(&controller);

	// Move
	Engine::Input::IAction* moveAction = nullptr;
	mappingContext->GetAction(L"Move", &moveAction);

	Engine::Input::Trigger::IDown* leftTrigger = nullptr;
	moveAction->GetTrigger(&leftTrigger);
	Engine::Input::Component::IButtonComponent* left = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::A, &left);
	leftTrigger->AddModifier(negative);
	leftTrigger->SetComponent(left);

	Engine::Input::Trigger::IDown* rightTrigger = nullptr;
	moveAction->GetTrigger(&rightTrigger);
	Engine::Input::Component::IButtonComponent* right = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::D, &right);
	rightTrigger->SetComponent(right);

	Engine::Input::Trigger::IDown* forwardTrigger = nullptr;
	moveAction->GetTrigger(&forwardTrigger);
	Engine::Input::Component::IButtonComponent* up = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::W, &up);
	forwardTrigger->AddModifier(swizzleAxis);
	forwardTrigger->SetComponent(up);

	Engine::Input::Trigger::IDown* backwardTrigger = nullptr;
	moveAction->GetTrigger(&backwardTrigger);
	Engine::Input::Component::IButtonComponent* down = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::S, &down);
	backwardTrigger->AddModifier(swizzleAxis);
	backwardTrigger->AddModifier(negative);
	backwardTrigger->SetComponent(down);

	Engine::Input::Trigger::IDown* leftStickXTrigger = nullptr;
	moveAction->GetTrigger(&leftStickXTrigger);
	Engine::Input::Component::IAxisComponent* leftStickX = nullptr;
	controller->GetComponent(Engine::Input::Device::IController::Thumb::LeftX, &leftStickX);
	leftStickXTrigger->SetComponent(leftStickX);

	Engine::Input::Trigger::IDown* leftStickYTrigger = nullptr;
	moveAction->GetTrigger(&leftStickYTrigger);
	Engine::Input::Component::IAxisComponent* leftStickY = nullptr;
	controller->GetComponent(Engine::Input::Device::IController::Thumb::LeftY, &leftStickY);
	leftStickYTrigger->SetComponent(leftStickY);
	leftStickYTrigger->AddModifier(swizzleAxis);

	// Jump
	Engine::Input::IAction* jumpAction = nullptr;
	mappingContext->GetAction(L"Jump", &jumpAction);

	Engine::Input::Trigger::IDown* keyTrigger = nullptr;
	jumpAction->GetTrigger(&keyTrigger);
	Engine::Input::Component::IButtonComponent* space = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::Space, &space);
	keyTrigger->SetComponent(space);

	Engine::Input::Trigger::IDown* buttonTrigger = nullptr;
	jumpAction->GetTrigger(&buttonTrigger);
	Engine::Input::Component::IButtonComponent* aButton = nullptr;
	controller->GetComponent(Engine::Input::Device::IController::Button::A, &aButton);
	buttonTrigger->SetComponent(aButton);

	// Temp
	Engine::Input::IAction* interactAction = nullptr;
	mappingContext->GetAction(L"Interact", &interactAction);

	Engine::Input::Trigger::IDown* eButtonTrigger = nullptr;
	interactAction->GetTrigger(&eButtonTrigger);
	Engine::Input::Component::IButtonComponent* E = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::E, &E);
	eButtonTrigger->SetComponent(E);

	Engine::Input::Trigger::IDown* xButtonTrigger = nullptr;
	interactAction->GetTrigger(&xButtonTrigger);
	Engine::Input::Component::IButtonComponent* xButton = nullptr;
	controller->GetComponent(Engine::Input::Device::IController::Button::X, &xButton);
	xButtonTrigger->SetComponent(xButton);
}

void GameClient::Application::DeclareCameraAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext)
{
	Engine::Input::Modifier::INegative* negative = nullptr;
	inputManager->GetModifier(&negative);
	Engine::Input::Modifier::ISwizzleAxis* swizzleAxis = nullptr;
	inputManager->GetModifier(Engine::Input::Modifier::ISwizzleAxis::Type::YXZ, &swizzleAxis);

	Engine::Input::IAction* action = nullptr;
	mappingContext->GetAction(L"Camera", &action);

	Engine::Input::Device::IMouse* mouse = nullptr;
	inputManager->GetDevice(&mouse);

	Engine::Input::Trigger::IDown* mouseXTrigger = nullptr;
	action->GetTrigger(&mouseXTrigger);
	Engine::Input::Component::IAxisComponent* mouseXAxis = nullptr;
	mouse->GetComponent(Engine::Input::Device::IMouse::Axis::X, &mouseXAxis);
	mouseXTrigger->SetComponent(mouseXAxis);
	mouseXTrigger->AddModifier(swizzleAxis);

	Engine::Input::Trigger::IDown* mouseYTrigger = nullptr;
	action->GetTrigger(&mouseYTrigger);
	Engine::Input::Component::IAxisComponent* mouseYAxis = nullptr;
	mouse->GetComponent(Engine::Input::Device::IMouse::Axis::Y, &mouseYAxis);
	mouseYTrigger->SetComponent(mouseYAxis);

	Engine::Input::Device::IController* controller = nullptr;
	inputManager->GetDevice(&controller);

	Engine::Input::Trigger::IDown* rightStickXTrigger = nullptr;
	action->GetTrigger(&rightStickXTrigger);
	Engine::Input::Component::IAxisComponent* rightStickX = nullptr;
	controller->GetComponent(Engine::Input::Device::IController::Thumb::RightX, &rightStickX);
	rightStickXTrigger->SetComponent(rightStickX);
	rightStickXTrigger->AddModifier(swizzleAxis);

	Engine::Input::Trigger::IDown* rightStickYTrigger = nullptr;
	action->GetTrigger(&rightStickYTrigger);
	Engine::Input::Component::IAxisComponent* rightStickY = nullptr;
	controller->GetComponent(Engine::Input::Device::IController::Thumb::RightY, &rightStickY);
	rightStickYTrigger->SetComponent(rightStickY);
	rightStickYTrigger->AddModifier(negative);
}

void GameClient::Application::DeclareSystemAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext)
{
	Engine::Input::Device::IMouse* mouse = nullptr;
	inputManager->GetDevice(&mouse);

	Engine::Input::Device::IKeyboard* keyboard = nullptr;
	inputManager->GetDevice(&keyboard);

	Engine::Input::Device::IController* controller = nullptr;
	inputManager->GetDevice(&controller);

	Engine::Input::IAction* unlockAction = nullptr;
	mappingContext->GetAction(L"UnlockCursor", &unlockAction);

	Engine::Input::Trigger::IDown* f1Trigger = nullptr;
	unlockAction->GetTrigger(&f1Trigger);
	Engine::Input::Component::IButtonComponent* f1 = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::F1, &f1);
	f1Trigger->SetComponent(f1);

	unlockAction->AddListener(Engine::Input::Trigger::Event::Started, [mouse](auto) {
		mouse->ShowCursor();
		mouse->UnlockCursor();
		});

	Engine::Input::IAction* lockAction = nullptr;
	mappingContext->GetAction(L"LockCursor", &lockAction);

	Engine::Input::Trigger::IDown* f2Trigger = nullptr;
	lockAction->GetTrigger(&f2Trigger);
	Engine::Input::Component::IButtonComponent* f2 = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::F2, &f2);
	f2Trigger->SetComponent(f2);

	lockAction->AddListener(Engine::Input::Trigger::Event::Started, [mouse](auto) {
		mouse->HideCursor();
		mouse->LockCursor();
		});

	Engine::Input::IAction* showAction = nullptr;
	mappingContext->GetAction(L"ShowCursor", &showAction);

	Engine::Input::Trigger::IDown* mouseXTrigger = nullptr;
	showAction->GetTrigger(&mouseXTrigger);
	Engine::Input::Component::IAxisComponent* mouseXAxis = nullptr;
	mouse->GetComponent(Engine::Input::Device::IMouse::Axis::X, &mouseXAxis);
	mouseXTrigger->SetComponent(mouseXAxis);

	Engine::Input::Trigger::IDown* mouseYTrigger = nullptr;
	showAction->GetTrigger(&mouseYTrigger);
	Engine::Input::Component::IAxisComponent* mouseYAxis = nullptr;
	mouse->GetComponent(Engine::Input::Device::IMouse::Axis::Y, &mouseYAxis);
	mouseYTrigger->SetComponent(mouseYAxis);

	showAction->AddListener(Engine::Input::Trigger::Event::Started, [mouse](auto value) {
		if (mouse->IsCursorLocked() == false) mouse->ShowCursor();
		});

	Engine::Input::IAction* hideAction = nullptr;
	mappingContext->GetAction(L"HideCursor", &hideAction);

	Engine::Input::Trigger::IDown* rightStickXTrigger = nullptr;
	hideAction->GetTrigger(&rightStickXTrigger);
	Engine::Input::Component::IAxisComponent* rightStickX = nullptr;
	controller->GetComponent(Engine::Input::Device::IController::Thumb::RightX, &rightStickX);
	rightStickXTrigger->SetComponent(rightStickX);

	Engine::Input::Trigger::IDown* rightStickYTrigger = nullptr;
	hideAction->GetTrigger(&rightStickYTrigger);
	Engine::Input::Component::IAxisComponent* rightStickY = nullptr;
	controller->GetComponent(Engine::Input::Device::IController::Thumb::RightY, &rightStickY);
	rightStickYTrigger->SetComponent(rightStickY);

	hideAction->AddListener(Engine::Input::Trigger::Event::Started, [mouse](auto value) {
		mouse->HideCursor();
		});
}
