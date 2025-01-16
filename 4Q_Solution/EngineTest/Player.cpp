#include "pch.h"
#include "Player.h"

void Player::PreInitialize()
{
	Object::PreInitialize();
	const auto inputManager = Engine::Application::GetInputManager();
	inputManager->AddActionListener(L"Move", DSH::Input::Trigger::Event::Triggered, [this](const DSH::Input::Value value)
	{
		_movement->SetDirection(value);
	});
}
