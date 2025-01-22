#pragma once


class RemoteMoveComponent : public Engine::Component::Component
{
public:
	RemoteMoveComponent();

	void SetTarget(Engine::Transform* target);
	void SetSpeed(float speed);
	void SetDirection(Engine::Math::Vector3 direction);
	void SetNextLocation(Engine::Math::Vector3 location);

	void Update(float deltaTime) override;

private:
	float _speed;
	Engine::Math::Vector3 _direction;
	Engine::Math::Vector3 _nextLocation;
	Engine::Transform* _target;
};

