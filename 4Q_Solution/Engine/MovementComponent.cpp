#include "pch.h"
#include "MovementComponent.h"

Engine::Component::MovementComponent::MovementComponent() :
	_speed(1.f),
	_direction(Math::Vector3::Zero)
{
}

void Engine::Component::MovementComponent::SetSpeed(const float speed)
{
	_speed = speed;
}

float Engine::Component::MovementComponent::GetSpeed() const
{
	return _speed;
}

void Engine::Component::MovementComponent::SetDirection(const Math::Vector3 direction)
{
	_direction = direction;
}
