#include "pch.h"
#include "RemoteMoveComponent.h"

RemoteMoveComponent::RemoteMoveComponent() :
	_speed(0.f), 
	_direction(Engine::Math::Vector3::Zero), 
	_target(nullptr), 
	_nextLocation(Engine::Math::Vector3::Zero)
{

}

void RemoteMoveComponent::SetTarget(Engine::Transform* target)
{
	_target = target;
}

void RemoteMoveComponent::SetSpeed(float speed)
{
	_speed = speed;
}

void RemoteMoveComponent::SetDirection(Engine::Math::Vector3 direction)
{
	_direction = direction;
}

void RemoteMoveComponent::SetNextLocation(Engine::Math::Vector3 location)
{
	_nextLocation = location;
}

void RemoteMoveComponent::Update(float deltaTime)
{
	Component::Update(deltaTime);

	Engine::Math::Vector3 currentLocation = _target->position;
	
	static float elapsed;
	elapsed += deltaTime;
	float maxElapseTime = 0.2f;

	float t = std::clamp(elapsed / maxElapseTime, 0.0f, 1.0f);

	float x = std::lerp(currentLocation.x, _nextLocation.x, t);
	float y = std::lerp(currentLocation.y, _nextLocation.y, t);
	float z = std::lerp(currentLocation.z, _nextLocation.z, t);

	Engine::Math::Vector3 lerpedLocation(x, y, z);
	if (elapsed >= maxElapseTime) {
		elapsed -= maxElapseTime;
	}
	_target->Translate(lerpedLocation);

}
