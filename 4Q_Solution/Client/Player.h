#pragma once

class GrabbedObject;

class Player : public Engine::Object
{
	enum StateFlag : unsigned long long
	{
		Idle				= 1 << 0,
		Walk				= 1 << 1,
		Jump				= 1 << 2,
		Interact			= 1 << 3,
		Jump_Started		= 1 << 4,
		Jump_Triggered		= 1 << 5,
		Interact_Started	= 1 << 6,
		Interact_Triggered	= 1 << 7,
		Interact_Completed	= 1 << 8
	};

	enum SplitType { Lower, Upper, End };
public:
	Player();

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

	void SetCapsuleScale(Engine::Math::Vector3 capsuleScale);
protected:
	void DisposeComponents() override;

	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;
	void PostUpdate(float deltaTime) override;
	void PostAttach() override;

private:
	void MoveStarted();
	void MoveTriggered(Engine::Math::Vector3 value);
	void MoveCompleted();

	void JumpStarted();

	void InteractStarted();
	void InteractTriggered();
	void InteractCompleted();

	void ChangeSplitAnimation(const char* animation, StateFlag flag, SplitType type);
	void SyncPatialAnimation(const char* animation, StateFlag flag, SplitType parent, SplitType child);
private:
	void SendStateMessage();

protected:
	std::filesystem::path _meshPath;
	Engine::Math::Matrix _worldMatrix;

	Engine::Component::Movement* _movement;
	Engine::Component::Camera* _camera;
	Engine::Component::SkeletalMesh* _skeletalMesh;
	Engine::Component::Animator* _animator;
	Engine::Component::FixedArm* _fixedArm;

	Engine::Component::ChractorController* _rigid;
	Engine::Component::Synchronize* _sync;
	RemoteMove* _remote;

	Engine::Component::BitFlag* _bitFlag;

protected:
	Engine::Math::Vector3 _capsuleScale;
	Engine::Math::Quaternion _offset;
	float _speed;


	GrabbedObject* grabbedObject;

private:
	// State Test
	void UpdateState();

public:
	void SetSerialNumber(int num);
	const int GetSerialNumber() const;
	void SyncMove(const MoveMsg::MoveSync* msg);
	// 이 함수는 최초 입장 했을 때 초기 위치 설정을 위한 함수입니다.
	void SetLocation(const MoveMsg::MoveSync* msg);
};

