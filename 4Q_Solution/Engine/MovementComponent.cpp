#include "pch.h"
#include "MovementComponent.h"

void Engine::Component::MovementComponent::Initialize()
{
	Component::Initialize();
}

void Engine::Component::MovementComponent::SetSpeed(const float speed)
{
	_speed = speed;
}

float Engine::Component::MovementComponent::GetSpeed() const
{
	return _speed;
}
