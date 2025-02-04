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

	void OnHit(Engine::Physics::ContactEvent info);
private:
	Engine::Component::Movement _movement;
	Engine::Component::Camera _camera;
	//Engine::Component::StaticMesh _staticMesh;
	Engine::Component::SkeletalMesh _skeltalMesh;
	Engine::Component::Animator _animator;
	Engine::Math::Matrix _worldMatrix;
	Engine::Component::TextRenderer _textRenderer;
	Engine::Component::Synchronize _sync;

	Engine::Component::RigidDynamic _rigid;

	Engine::Component::RigidDynamic _tempOtherRigid;
};

//class RemotePlayer : public Engine::Object
//{
//public:
//	RemotePlayer();
//protected:
//	void Addition() override;
//
//private:
//	Engine::Component::SkeletalMesh _skeltalMesh;
//	Engine::Component::Animator _animator;
//	Engine::Math::Matrix _worldMatrix;
//};