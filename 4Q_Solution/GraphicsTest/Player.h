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
	void PostUpdate(float deltaTime) override;

	void PostFixedUpdate() override;
private:
	Engine::Component::MovementComponent _movement;
	Engine::Component::CameraComponent _camera;
	//Engine::Component::StaticMesh _staticMesh;
	Engine::Component::SkeletalMesh _skeltalMesh;
	Engine::Component::Animator _animator;
	Engine::Math::Matrix _worldMatrix;
	Engine::Component::TextRenderer _textRenderer;
	Engine::Math::Vector3 _camRotation;
};

class TestPlayer : public Engine::Object
{public:
	TestPlayer();
protected:
	void Addition() override;
	void PostInitialize() override;
	void PostUpdate(float deltaTime) override;

private:
	Engine::Component::StaticMesh _staticMesh;
	Engine::Math::Matrix _worldMatrix;
};