#include "pch.h"
#include "Movement.h"

Engine::Component::Movement::Movement() :
	_speed(1.f), _direction(Math::Vector3::Zero), _target(nullptr)
{
}

void Engine::Component::Movement::SetTarget(Transform* target)
{
	_target = target;
}

void Engine::Component::Movement::SetSpeed(const float speed)
{
	_speed = speed;
}

float Engine::Component::Movement::GetSpeed() const
{
	return _speed;
}

void Engine::Component::Movement::SetDirection(const Math::Vector3 direction)
{
	_direction = direction;
}

Engine::Math::Vector3 Engine::Component::Movement::GetDirection() const
{
	return _direction;
}

void Engine::Component::Movement::Update(const float deltaTime)
{
	Component::Update(deltaTime);
	_target->Translate(_direction * (_speed * deltaTime));
}
