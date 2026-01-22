#include "pch.h"
#include "Movement.h"

Engine::Component::Movement::Movement() :
	_speed(1.f), _direction(Math::Vector3::Zero), 
	_target(nullptr), _isMoving(false), _isMoved(false)
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
	UpdateVelocity(deltaTime);
	_target->Translate(_velocity);	

	SetIsMoving(_direction != Math::Vector3::Zero);
}

void Engine::Component::Movement::FixedUpdate()
{

}

void Engine::Component::Movement::BindOnMove(std::function<void()> onMove)
{
	_onMove = onMove;
}

void Engine::Component::Movement::BindOnStop(std::function<void()> onStop)
{
	_onStop = onStop;
}

void Engine::Component::Movement::UpdateVelocity(float deltaTime)
{
	_velocity = _direction * (_speed * deltaTime);
}

void Engine::Component::Movement::SetIsMoving(bool isMoving)
{
	_isMoved = _isMoving;
	_isMoving = isMoving;
	if (_onMove != nullptr &&
		_isMoving == true &&
		_isMoved == false)
	{
		_onMove();
	}

	if (_onStop != nullptr &&
		_isMoving == false &&
		_isMoved == true)
	{
		_onStop();
	}
}

