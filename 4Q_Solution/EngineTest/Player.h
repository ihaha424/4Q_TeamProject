#pragma once

class Player : public Engine::Object
{
public:
	Player();
protected:
	void Addition() override;
	void PreInitialize() override;
	void PostInitialize() override;
	void PostAttach() override;

private:
	Engine::Component::MovementComponent _movement;
	Engine::Component::CameraComponent _camera;
	Engine::Component::StaticMesh _staticMesh;
	Engine::Component::Light _tempLight;
};

