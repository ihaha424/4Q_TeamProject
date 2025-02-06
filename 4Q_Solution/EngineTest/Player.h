#pragma once
#include "RemoteMoveComponent.h"
#include "../Packet/ProtoInclude.h"

class Player : public Engine::Object
{
public:
	Player(std::filesystem::path&& meshPath, std::filesystem::path&& fontPath);

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
	int GetSerialNumber();
	void SetSerialNumber(int num);
protected:
	void DisposeComponents() override;

	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;
	void PostAttach() override;
	void PostUpdate(float deltaTime) override;

	void PostFixedUpdate() override;

	void EnterSuccess(const ConnectMsg::EnterAccept* msg);
	void SyncMove(const MoveMsg::MoveSync* msg);
	void SetLocation(const MoveMsg::MoveSync* msg);
private:
	std::filesystem::path _meshPath;
	std::filesystem::path _fontPath;

	Engine::Component::Camera* _camera;
	//Engine::Component::StaticMesh* _staticMesh;
	Engine::Component::SkeletalMesh* _skeltalMesh;
	Engine::Component::Animator* _animator;
	Engine::Math::Matrix _worldMatrix;
	Engine::Component::TextRenderer* _textRenderer;
	Engine::Component::Synchronize* _sync;
	RemoteMoveComponent* _remote;

	Engine::Math::Matrix _cameraParentMatrix;
	Engine::Math::Vector3 _cameraRotation;

	//Physics
	Engine::Component::ChractorController* _chractorController;
	unsigned short gravityFlag = true;

	// FixedArm
	Engine::Component::FixedArm* _fixedArm;
};
