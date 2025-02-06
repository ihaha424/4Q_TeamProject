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
	objectFactory->Register<Terrain>(L"../Resources/Level/Landscape03.fbx", "../Resources/Terrain/testTest.png");
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
	inputManager->GetModifier(&negative);
	Engine::Input::Modifier::ISwizzleAxis* swizzleAxis = nullptr;
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
	leftStickXTrigger->SetComponent(leftStickX);

	Engine::Input::Trigger::IDown* leftStickYTrigger = nullptr;
	action->GetTrigger(&leftStickYTrigger);
	Engine::Input::Component::IAxisComponent* leftStickY = nullptr;
	controller->GetComponent(Engine::Input::Device::IController::Thumb::LeftY, &leftStickY);
	leftStickYTrigger->SetComponent(leftStickY);
	leftStickYTrigger->AddModifier(swizzleAxis);
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
