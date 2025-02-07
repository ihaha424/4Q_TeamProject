#include "pch.h"
#include "RemoteMove.h"

RemoteMove::RemoteMove() :
	_nextLocation(Engine::Math::Vector3::Zero)
{

}

void RemoteMove::SetNextLocation(Engine::Math::Vector3 location)
{
	_nextLocation = location;
	_dtLocation = _nextLocation - _target->position;
}

void RemoteMove::Update(float deltaTime)
{
	SetIsMoving(_direction != Engine::Math::Vector3::Zero);
	if (_isMoving)
	{
		UpdateVelocity(deltaTime);
		_target->Translate(_velocity);
	}
	else
	{
		Engine::Math::Vector3 currentLocation = _target->position;

		static float elapsed;
		elapsed += deltaTime;
		float maxElapseTime = 0.5f;

		float t = std::clamp(elapsed / maxElapseTime, 0.0f, 1.0f);

		Engine::Math::Vector3 lerpedLocation(Engine::Math::Vector3::Zero);

		lerpedLocation = Engine::Math::EasingInterpolation(currentLocation, _nextLocation, t);

		if (elapsed >= maxElapseTime) {
			elapsed -= maxElapseTime;
		}
		_target->position = lerpedLocation;
		//_target->position = _nextLocation;
	}
}

void RemoteMove::UpdateVelocity(float deltaTime)
{
	_velocity = _direction * (_speed * deltaTime) + (_dtLocation * deltaTime * 20);
}
