#pragma once
//#include "RayState.h"

class Ray : public Engine::Object
{
public:
	Ray(std::filesystem::path&& meshPath);

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	void SetCapsuleScale(Engine::Math::Vector3 capsuleScale);
protected:
	void DisposeComponents() override;

	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;
	void PostUpdate(float deltaTime) override;
	void PostAttach() override;

private:
	std::filesystem::path _meshPath;

	Engine::Component::Movement* _movement;
	Engine::Component::Camera* _camera;
	Engine::Component::SkeletalMesh* _skeletalMesh;
	Engine::Component::Animator* _animator;
	Engine::Component::FixedArm* _fixedArm;
	Engine::Math::Matrix _worldMatrix;

	Engine::Component::ChractorController* _rigid;
	RemoteMove* _remote;

private:
	Engine::Math::Vector3 _capsuleScale;
	Engine::Math::Quaternion _offset;

public:
	void SyncMove(const MoveMsg::MoveSync* msg);
	// 이 함수는 최초 입장 했을 때 초기 위치 설정을 위한 함수입니다.
	void SetLocation(const MoveMsg::MoveSync* msg);
};