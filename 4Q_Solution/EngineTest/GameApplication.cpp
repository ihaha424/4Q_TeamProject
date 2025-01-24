#include "pch.h"
#include "GameApplication.h"

#include "TestWorld.h"

GameApplication::GameApplication(const HINSTANCE instanceHandle) :
	Application(instanceHandle)
{
}

void GameApplication::DeclareInputActions(Engine::Input::IManager* inputManager)
{
    Application::DeclareInputActions(inputManager);

    Engine::Input::IMappingContext* mappingContext = nullptr;
    inputManager->GetMappingContext(L"Default", &mappingContext);

    DeclareMoveAction(inputManager, mappingContext);
    DeclareCameraAction(inputManager, mappingContext);

    inputManager->SetActiveMappingContext(mappingContext);
}

void GameApplication::Register(Engine::Load::IManager* loadManager, Engine::Content::IManager* contentManager)
{
	if (const auto testWorldData =	loadManager->GetWorldConfigData(L"TestWorld"); testWorldData.has_value())
	{
		const auto argument1 = testWorldData->GetProperty<std::wstring>(L"Argument1");
		const auto argument2 = testWorldData->GetProperty<int>(L"Argument2");
		auto factory = contentManager->GetWorldFactory();
		factory.Register<TestWorld>(argument1.value_or(L"Hi"), argument2.value_or(1));
	}

	if (const auto playerData = loadManager->GetObjectConfigData(L"Player"); playerData.has_value())
	{
		const auto argument1 = playerData->GetProperty<int>(L"Argument1");
		const auto argument2 = playerData->GetProperty<int>(L"Argument2");
		auto factory = contentManager->GetObjectFactory();
		factory.Register<Player>(argument1.value_or(1), argument2.value_or(2));
	}

	if (const auto movementComponentData = loadManager->GetComponentConfigData(L"MovementComponent"); movementComponentData.has_value())
	{
		auto factory = contentManager->GetComponentFactory();
		factory.Register<Engine::Component::MovementComponent>();
	}
}

void GameApplication::InitializeContents()
{
	Application::InitializeContents();
	Attach(&_world);
}

void GameApplication::DeclareMoveAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext)
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
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::Left, &left);
	leftTrigger->AddModifier(negative);
	leftTrigger->SetComponent(left);

	Engine::Input::Trigger::IDown* rightTrigger = nullptr;
	action->GetTrigger(&rightTrigger);
	Engine::Input::Component::IButtonComponent* right = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::Right, &right);
	rightTrigger->SetComponent(right);

	Engine::Input::Trigger::IDown* upTrigger = nullptr;
	action->GetTrigger(&upTrigger);
	Engine::Input::Component::IButtonComponent* up = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::Up, &up);
	upTrigger->AddModifier(swizzleAxis);
	upTrigger->SetComponent(up);

	Engine::Input::Trigger::IDown* downTrigger = nullptr;
	action->GetTrigger(&downTrigger);
	Engine::Input::Component::IButtonComponent* down = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::Down, &down);
	downTrigger->AddModifier(swizzleAxis);
	downTrigger->AddModifier(negative);
	downTrigger->SetComponent(down);
}

void GameApplication::DeclareCameraAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext)
{
	Engine::Input::Modifier::INegative* negative = nullptr;
	Engine::Input::Modifier::ISwizzleAxis* swizzleAxis = nullptr;
	inputManager->GetModifier(&negative);
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

	Engine::Input::Trigger::IDown* yTrigger = nullptr;
	action->GetTrigger(&yTrigger);
	yTrigger->AddModifier(swizzleAxis);
	yTrigger->SetComponent(yAxis);
}