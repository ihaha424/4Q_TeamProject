#pragma once

class Player : public Engine::Object
{
public:
	Player();
	Player(int argument1, int argument2); // TODO: Temporary
protected:
	void Addition() override;
	void PreInitialize() override;
	void PostInitialize() override;
	void PostAttach() override;
	void PostUpdate(float deltaTime) override;

private:
	Engine::Component::MovementComponent _movement;
	Engine::Component::CameraComponent _camera;
	Engine::Component::StaticMesh _staticMesh;
	//Engine::Component::SkeletalMesh _skeltalMesh;
	//Engine::Component::Animator _animator;
	Engine::Math::Matrix _worldMatrix;
	Engine::Component::TextRenderer _textRenderer;
};

class RemotePlayer : public Engine::Object
{
public:
	RemotePlayer();
protected:
	void Addition() override;

private:
	Engine::Component::SkeletalMesh _skeltalMesh;
	Engine::Component::Animator _animator;
	Engine::Math::Matrix _worldMatrix;
	
};