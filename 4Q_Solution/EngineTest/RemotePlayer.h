#pragma once
#include "RemoteMoveComponent.h"
#include "../Packet/ProtoInclude.h"

class RemotePlayer : public Engine::Object
{
public:
	explicit RemotePlayer(std::filesystem::path&& meshPath);
	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
	void DisposeComponents() override;

protected:
	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;
	void PostAttach() override;
	void PostUpdate(float deltaTime) override;

	void SyncMove(const MoveMsg::MoveSync* msg);
	void FirstInitialize(const ConnectMsg::SyncPlayer* msg);
	void StateChange(const MoveMsg::StateChange* msg);

private:
	std::filesystem::path _meshPath;

	//Engine::Component::MovementComponent _movement;
	//Engine::Component::CameraComponent _camera;
	//Engine::Component::StaticMesh _staticMesh;
	Engine::Component::SkeletalMesh* _skeletalMesh;
	Engine::Component::Animator* _animator;
	Engine::Math::Matrix _worldMatrix;
	Engine::Component::SynchronizeComponent* _sync;

	RemoteMoveComponent* _remoteMove;
};

