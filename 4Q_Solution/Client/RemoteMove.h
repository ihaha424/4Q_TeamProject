#pragma once


class RemoteMove : public Engine::Component::Movement
{
public:
	RemoteMove();

	void SetNextLocation(Engine::Math::Vector3 location);

	void Update(float deltaTime) override;

protected:
	void UpdateVelocity(float deltaTime) override;

private:
	Engine::Math::Vector3 _nextLocation;
	Engine::Math::Vector3 _dtLocation;

	float _elapsedTime;
};

