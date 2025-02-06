#include "pch.h"
#include "Application.h"

#include "TestWorld.h"

GameClient::Application::Application(const HINSTANCE instanceHandle) : Engine::Application(instanceHandle)
{
}

void GameClient::Application::LoadData(Engine::Load::IManager* loadManager)
{
	loadManager->LoadRegisterData(L"../Resources/JSONTest/MapData.json");
	loadManager->LoadCloneData(L"../Resources/JSONTest/MapData.json");
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
	objectFactory->Register<Ray>(L"../Resources/Test/Ray.fbx");
	objectFactory->Register<GlobalLight>();
	objectFactory->Register<Terrain>(L"../Resources/Level/Level.fbx", "../Resources/Terrain/testTest.png");
	objectFactory->Register<SkyBox>(L"../Resources/IBL/skybox.fbx");




	objectFactory->Register<Building1>(L"../Resources/TestObject/sphere.fbx", L"../Resources/TestObject/sphere.fbx");
	objectFactory->Register<Building2>(L"../Resources/TestObject/sphere.fbx", L"../Resources/TestObject/sphere.fbx");
	objectFactory->Register<Building3>(L"../Resources/TestObject/sphere.fbx", L"../Resources/TestObject/sphere.fbx");
	objectFactory->Register<Building4>(L"../Resources/TestObject/sphere.fbx", L"../Resources/TestObject/sphere.fbx");
	objectFactory->Register<Building5>(L"../Resources/TestObject/sphere.fbx", L"../Resources/TestObject/sphere.fbx");
	objectFactory->Register<Building6>(L"../Resources/TestObject/sphere.fbx", L"../Resources/TestObject/sphere.fbx");
	objectFactory->Register<Building7>(L"../Resources/TestObject/sphere.fbx", L"../Resources/TestObject/sphere.fbx");
	objectFactory->Register<Building8>(L"../Resources/TestObject/sphere.fbx", L"../Resources/TestObject/sphere.fbx");
	objectFactory->Register<Building9>(L"../Resources/TestObject/sphere.fbx", L"../Resources/TestObject/sphere.fbx");
	objectFactory->Register<Building10>(L"../Resources/TestObject/sphere.fbx", L"../Resources/TestObject/sphere.fbx");
	objectFactory->Register<SudiumBlue>(L"../Resources/TestObject/sphere.fbx", L"../Resources/TestObject/sphere.fbx");


}

void GameClient::Application::PrepareInitialWorld(Engine::Content::Factory::World* worldFactory)
{
	worldFactory->Clone<TestWorld>();
}

void GameClient::Application::DeclareMoveAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext)
{
	Engine::Input::Modifier::INegative* negative = nullptr;
	Engine::Input::Modifier::ISwizzleAxis* swizzleAxis = nullptr;
	inputManager->GetModifier(&negative);
	inputManager->GetModifier(Engine::Input::Modifier::ISwizzleAxis::Type::ZXY, &swizzleAxis);

	Engine::Input::IAction* action = nullptr;
	mappingContext->GetAction(L"Move", &action);

	Engine::Input::Device::IKeyboard* keyboard = nullptr;
	inputManager->GetDevice(&keyboard);

	Engine::Input::Trigger::IDown* leftTrigger = nullptr;
	action->GetTrigger(&leftTrigger);
	Engine::Input::Component::IButtonComponent* left = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::A, &left);
	leftTrigger->AddModifier(negative);
	leftTrigger->SetComponent(left);

	Engine::Input::Trigger::IDown* rightTrigger = nullptr;
	action->GetTrigger(&rightTrigger);
	Engine::Input::Component::IButtonComponent* right = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::D, &right);
	rightTrigger->SetComponent(right);

	Engine::Input::Trigger::IDown* forwardTrigger = nullptr;
	action->GetTrigger(&forwardTrigger);
	Engine::Input::Component::IButtonComponent* up = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::W, &up);
	forwardTrigger->AddModifier(swizzleAxis);
	forwardTrigger->SetComponent(up);

	Engine::Input::Trigger::IDown* backwardTrigger = nullptr;
	action->GetTrigger(&backwardTrigger);
	Engine::Input::Component::IButtonComponent* down = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::S, &down);
	backwardTrigger->AddModifier(swizzleAxis);
	backwardTrigger->AddModifier(negative);
	backwardTrigger->SetComponent(down);

	Engine::Input::Device::IController* controller = nullptr;
	inputManager->GetDevice(&controller);

	Engine::Input::Trigger::IDown* leftStickXTrigger = nullptr;
	action->GetTrigger(&leftStickXTrigger);
	Engine::Input::Component::IAxisComponent* leftStickX = nullptr;
	controller->GetComponent(Engine::Input::Device::IController::Thumb::LeftX, &leftStickX);
}

void GameClient::Application::DeclareCameraAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext)
{
	Engine::Input::Modifier::ISwizzleAxis* swizzleAxis = nullptr;
	inputManager->GetModifier(Engine::Input::Modifier::ISwizzleAxis::Type::YXZ, &swizzleAxis);

	Engine::Input::IAction* action = nullptr;
	mappingContext->GetAction(L"Camera", &action);

	Engine::Input::Device::IMouse* mouse = nullptr;
	inputManager->GetDevice(&mouse);

	Engine::Input::Component::IAxisComponent* xAxis = nullptr;
	mouse->GetComponent(Engine::Input::Device::IMouse::Axis::X, &xAxis);
	Engine::Input::Component::IAxisComponent* yAxis = nullptr;
	mouse->GetComponent(Engine::Input::Device::IMouse::Axis::Y, &yAxis);

	Engine::Input::Trigger::IDown* xTrigger = nullptr;
	action->GetTrigger(&xTrigger);
	xTrigger->SetComponent(xAxis);
	xTrigger->AddModifier(swizzleAxis);

	Engine::Input::Trigger::IDown* yTrigger = nullptr;
	action->GetTrigger(&yTrigger);
	yTrigger->SetComponent(yAxis);
}

void GameClient::Application::DeclareSystemAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext)
{
	Engine::Input::Device::IMouse* mouse = nullptr;
	inputManager->GetDevice(&mouse);

	Engine::Input::Device::IKeyboard* keyboard = nullptr;
	inputManager->GetDevice(&keyboard);

	Engine::Input::IAction* unlockShowAction = nullptr;
	mappingContext->GetAction(L"UnlockShow", &unlockShowAction);

	Engine::Input::Trigger::IDown* f1Trigger = nullptr;
	unlockShowAction->GetTrigger(&f1Trigger);
	Engine::Input::Component::IButtonComponent* f1 = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::F1, &f1);
	f1Trigger->SetComponent(f1);

	unlockShowAction->AddListener(Engine::Input::Trigger::Event::Started, [mouse](auto) {
		mouse->ShowCursor();
		mouse->UnlockCursor();
		});

	Engine::Input::IAction* lockHideAction = nullptr;
	mappingContext->GetAction(L"LockHide", &lockHideAction);

	Engine::Input::Trigger::IDown* f2Trigger = nullptr;
	lockHideAction->GetTrigger(&f2Trigger);
	Engine::Input::Component::IButtonComponent* f2 = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::F2, &f2);
	f2Trigger->SetComponent(f2);

	lockHideAction->AddListener(Engine::Input::Trigger::Event::Started, [mouse](auto) {
		mouse->HideCursor();
		mouse->LockCursor();
		});
}
