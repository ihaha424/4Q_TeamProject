#include "pch.h"
#include "GameApplication.h"

#include "TestWorld.h"

GameApplication::GameApplication(const HINSTANCE instanceHandle) :
	Application(instanceHandle)
{
}

void GameApplication::DeclareInputActions(Engine::Input::IManager* inputManager)
{
	Engine::Input::Device::IMouse* mouse = nullptr;
	inputManager->GetDevice(&mouse);
	mouse->LockCursor();
	mouse->HideCursor();

    Engine::Input::IMappingContext* mappingContext = nullptr;
    inputManager->GetMappingContext(L"Default", &mappingContext);


    //DeclareMoveAction(inputManager, mappingContext);
    //DeclareCameraAction(inputManager, mappingContext);
	DeclareSystemAction(inputManager, mappingContext);

    inputManager->SetActiveMappingContext(mappingContext);
}

void GameApplication::Register(Engine::Content::IManager* contentManager)
{
	Application::Register(contentManager);
	const auto worldFactory = contentManager->GetWorldFactory();
	worldFactory->Register<TestWorld>();
	const auto objectFactory = contentManager->GetObjectFactory();
	objectFactory->Register<Player>(L"../Resources/Player/Player.X", L"../Resources/Font/Gungseo12.sfont");
	objectFactory->Register<RemotePlayer>(L"../Resources/Player/Player.X");
	objectFactory->Register<GlobalLight>();
	objectFactory->Register<Terrain>(L"../Resources/Level/Level.fbx");
	objectFactory->Register<Cube>(L"../Resources/FBX/char.fbx");
	//objectFactory->Register<Sphere>(L"../Resources/TestObject/sphere.fbx");
	const auto componentFactory = contentManager->GetComponentFactory();
	componentFactory->Register<RemoteMoveComponent>();
}

void GameApplication::PrepareInitialWorld(Engine::Content::Factory::World* worldFactory)
{
	worldFactory->Clone<TestWorld>();
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

	Engine::Input::IAction* jumpAction = nullptr;
	mappingContext->GetAction(L"Jump", &jumpAction);
	Engine::Input::Trigger::IDown* jumpTrigger = nullptr;
	jumpAction->GetTrigger(&jumpTrigger);
	Engine::Input::Component::IButtonComponent* jump = nullptr;
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::Space, &jump);
	jumpTrigger->SetComponent(jump);

	//Engine::Input::Trigger::IDown* jumpTrigger = nullptr;
	//action->GetTrigger(&jumpTrigger);
	//Engine::Input::Component::IButtonComponent* jump = nullptr;
	//keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::Space, &jump);
	////jumpTrigger->AddModifier(swizzleAxis);
	////jumpTrigger->AddModifier(negative);
	//jumpTrigger->SetComponent(jump);
}

void GameApplication::DeclareCameraAction(Engine::Input::IManager* inputManager, Engine::Input::IMappingContext* mappingContext)
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

	Engine::Input::Trigger::IDown* yTrigger = nullptr;
	action->GetTrigger(&yTrigger);
	yTrigger->AddModifier(swizzleAxis);
	yTrigger->SetComponent(yAxis);
}

void GameApplication::DeclareSystemAction(Engine::Input::IManager* inputManager,
	Engine::Input::IMappingContext* mappingContext)
{
	Engine::Input::Modifier::ISwizzleAxis* swizzleAxis = nullptr;
	inputManager->GetModifier(Engine::Input::Modifier::ISwizzleAxis::Type::YXZ, &swizzleAxis);

	Engine::Input::IAction* action = nullptr;
	mappingContext->GetAction(L"System", &action);

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
	//action->AddListener(Engine::Input::Trigger::Event::Started, [](auto value)
	//{
	//	GetLoggerManager()->Log(Engine::Logger::LogLevel::Trace, std::format(L"x:{} \t y:{} \t z:{}", value.x, value.y, value.z));
	//});

	action->AddListener(Engine::Input::Trigger::Event::Triggered, [](auto value)
	{
		GetLoggerManager()->Log(Engine::Logger::LogLevel::Debug, std::format(L"x:{} \t y:{} \t z:{}", value.x, value.y, value.z));
	});
	//action->AddListener(Engine::Input::Trigger::Event::Completed, [](auto value)
	//	{
	//		GetLoggerManager()->Log(Engine::Logger::LogLevel::Warning, std::format(L"x:{} \t y:{} \t z:{}", value.x, value.y, value.z));
	//	});
}
