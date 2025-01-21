#include "pch.h"
#include "Player.h"

void Player::PreInitialize()
{
	Object::PreInitialize();

	AddComponent(&_movement);
	_movement.SetTarget(&_transform);

	const auto inputManager = Engine::Application::GetInputManager();
	Engine::Input::IMappingContext* mappingContext = nullptr;
	inputManager->GetMappingContext(L"Default", &mappingContext);
	Engine::Input::IAction* action = nullptr;
	mappingContext->GetAction(L"Move", &action);
	action->AddListener(Engine::Input::Trigger::Triggered, [this](auto value) { _movement.SetDirection(value); });
}
