#include "pch.h"
#include "MovementComponent.h"

Engine::Component::MovementComponent::MovementComponent() :
	_speed(1.f), _direction(Math::Vector3::Zero), _target(nullptr)
{
}

void Engine::Component::MovementComponent::SetTarget(Transform* target)
{
	_target = target;
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

void Engine::Component::MovementComponent::Update(const float deltaTime)
{
	Component::Update(deltaTime);
	_target->Translate(_direction * (_speed * deltaTime));
}
