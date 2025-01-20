#include "pch.h"
#include "GameApplication.h"

#include "TestWorld.h"
#include "../Engine/SafeRelease.h"
#include "../Engine/ThrowIfFailed.h"

GameApplication::GameApplication(const HINSTANCE instanceHandle) :
	Application(instanceHandle, L"Test", SIZE{ 1920, 1080 })
{
}

void GameApplication::DeclareInputActions(Engine::Input::IManager* inputManager)
{
	Application::DeclareInputActions(inputManager);

	Engine::Input::Modifier::INegative* negative = nullptr;

	Engine::Input::Modifier::ISwizzleAxis* swizzleAxis = nullptr;
	inputManager->GetModifier(&negative);
	inputManager->GetModifier(Engine::Input::Modifier::ISwizzleAxis::Type::YXZ, &swizzleAxis);

	Engine::Input::IMappingContext* mappingContext = nullptr;
	inputManager->GetMappingContext(L"Default", &mappingContext);

	Engine::Input::IAction* moveAction = nullptr;
	mappingContext->GetAction(L"Move", &moveAction);

	Engine::Input::Trigger::IDown* leftTrigger = nullptr;
	moveAction->GetTrigger(&leftTrigger);

	leftTrigger->AddModifier(negative);

	Engine::Input::Component::IButtonComponent* left = nullptr;
	Engine::Input::Device::IKeyboard* keyboard = nullptr;
	inputManager->GetDevice(&keyboard);
	keyboard->GetComponent(Engine::Input::Device::IKeyboard::Key::Left, &left);
	leftTrigger->SetComponent(left);

	inputManager->SetActiveMappingContext(mappingContext);
}