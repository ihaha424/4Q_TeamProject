#pragma once


class RemoteMoveComponent : public Engine::Component::Movement
{
public:
	RemoteMoveComponent();

	void SetNextLocation(Engine::Math::Vector3 location);

	void Update(float deltaTime) override;

protected:
	void UpdateVelocity(float deltaTime) override;

private:
	Engine::Math::Vector3 _nextLocation;
	Engine::Math::Vector3 _dtLocation;

	float _elapsedTime;
};

