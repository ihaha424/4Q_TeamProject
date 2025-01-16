#include "pch.h"
#include "Player.h"

void Player::PreInitialize()
{
	Object::PreInitialize();
	auto inputManager = Engine::Application::GetInputManager();
}
