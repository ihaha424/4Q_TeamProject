#include "pch.h"
#include "GameApplication.h"

#include "TestWorld.h"
#include "../Engine/SafeRelease.h"
#include "../Engine/ThrowIfFailed.h"

GameApplication::GameApplication(const HINSTANCE instanceHandle) :
	Application(instanceHandle, L"Test", SIZE{ 1920, 1080 })
{
}

void GameApplication::DeclareInputActions(Engine::Manager::IInput* inputManager)
{
	Application::DeclareInputActions(inputManager);

	constexpr Engine::Utility::ThrowIfFailed thrower;
	constexpr Engine::Utility::SafeRelease releaser;

	const auto system = inputManager->GetSystem();
	DSH::Input::Modifier::INegative* negative = nullptr;
	DSH::Input::Modifier::ISwizzleAxis* swizzleAxis = nullptr;
	thrower(system->CreateModifier(&negative));
	thrower(system->CreateModifier(&swizzleAxis));
	swizzleAxis->SetType(DSH::Input::Modifier::ISwizzleAxis::Type::YXZ);

	const auto mappingContext = inputManager->GetMappingContext();
	DSH::Input::IAction* action = nullptr;
	thrower(mappingContext->GetAction(L"Move", &action));

	DSH::Input::Trigger::IDown* leftTrigger = nullptr;
	DSH::Input::Trigger::IDown* rightTrigger = nullptr;
	DSH::Input::Trigger::IDown* upTrigger = nullptr;
	DSH::Input::Trigger::IDown* downTrigger = nullptr;
	thrower(action->GetTrigger(&leftTrigger));
	thrower(action->GetTrigger(&rightTrigger));
	thrower(action->GetTrigger(&upTrigger));
	thrower(action->GetTrigger(&downTrigger));

	const auto keyboard = inputManager->GetKeyboard();
	DSH::Input::Component::IButtonComponent* left = nullptr;
	DSH::Input::Component::IButtonComponent* right = nullptr;
	DSH::Input::Component::IButtonComponent* up = nullptr;
	DSH::Input::Component::IButtonComponent* down = nullptr;
	thrower(keyboard->GetComponent(DSH::Input::Device::IKeyboard::Key::Left, &left));
	thrower(keyboard->GetComponent(DSH::Input::Device::IKeyboard::Key::Right, &right));
	thrower(keyboard->GetComponent(DSH::Input::Device::IKeyboard::Key::Up, &up));
	thrower(keyboard->GetComponent(DSH::Input::Device::IKeyboard::Key::Down, &down));

	leftTrigger->SetComponent(left);
	leftTrigger->AddModifier(negative);
	rightTrigger->SetComponent(right);
	upTrigger->SetComponent(up);
	downTrigger->SetComponent(down);
	downTrigger->AddModifier(negative);
	downTrigger->AddModifier(swizzleAxis);

	releaser(&negative);
	releaser(&swizzleAxis);
}
