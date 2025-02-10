#include "pch.h"
#include "Remote.h"

Remote::Remote() :
	//, _movement(nullptr)
	_skeletalMesh(nullptr)
	, _animator(nullptr), _rigid(nullptr), _bitFlag(nullptr)
	, _offset(Engine::Math::Quaternion::CreateFromYawPitchRoll(std::numbers::pi_v<float>, 0, 0))
{
}

void Remote::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	//_movement = componentFactory->Clone<Engine::Component::Movement>(this);
	_skeletalMesh = componentFactory->Clone<Engine::Component::SkeletalMesh>(this);
	_animator = componentFactory->Clone<Engine::Component::Animator>(this);
	_rigid = componentFactory->Clone<Engine::Component::ChractorController>(this);
	_remote = componentFactory->Clone<RemoteMove>(this);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
	_bitFlag = componentFactory->Clone<Engine::Component::BitFlag>(this);
}

void Remote::SetCapsuleScale(Engine::Math::Vector3 capsuleScale)
{
	_capsuleScale = capsuleScale;
}

void Remote::DisposeComponents()
{
	//_movement->Dispose();
	_animator->Dispose();
	_skeletalMesh->Dispose();
	_rigid->Dispose();
	_remote->Dispose();
	_sync->Dispose();
	_bitFlag->Dispose();
}

void Remote::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	//_movement->SetTarget(&_transform);

	_skeletalMesh->SetFilePath(_meshPath);
	_skeletalMesh->SetMatrix(&_worldMatrix);
	_animator->SetSkeletalMesh(_skeletalMesh);


	_remote->SetTarget(&_transform);

	auto PhysicsManager = Engine::Application::GetPhysicsManager();

	Engine::Physics::ControllerDesc cd;
	cd.position = Engine::Math::Vector3(1115.f, 674.f, -872.f);
	cd.height = 10.f;
	cd.radius = 2.f;
	// TODO: Player Gravity
	cd.gravity = { 0.f, -9.8f, 0.f };
	cd.contactOffset = 0.1f;
	cd.stepOffset = 1.f;
	cd.slopeLimit = 0.707f;

	Engine::Physics::IController* controller;
	PhysicsManager->CreatePlayerController(&controller, PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene)), cd);
	_rigid->_controller = static_cast<Engine::Physics::Controller*>(controller);

	_rigid->_controller->SetMoveSpeed(0.f);

	// TODO: 적용해보고 속성값 조절
	// _rigid->_controller->SetBottomPosition({ 0,10,0 });

	// TODO: Camera Scene에 추가

	_sync->AddCallback((short)PacketID::MoveSync, &Remote::SyncMove, this);
	_sync->AddCallback((short)PacketID::DataRemote, &Remote::SetLocation, this);
	_sync->AddCallback((short)PacketID::StateChange, &Remote::StateChange, this);
}

void Remote::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	//_movement->SetSpeed(100.f);
	_remote->SetSpeed(100.f);

	//_skeltalMesh.SetRenderLayer(0);
	/*_animator.SetUpSplitBone(2);
	_animator.SplitBone(0, "Dummy_root");
	_animator.SplitBone(1, "Bip01-Spine1");
	_animator.ChangeAnimation("Wait");*/

	//_skeletalMesh->SetActiveShadow(false);
	_skeletalMesh->SetPostEffectFlag(1);
}


void Remote::PostUpdate(float deltaTime)
{
	Object::PostUpdate(deltaTime);

	Engine::Math::Quaternion q = Engine::Math::Quaternion::Concatenate(_transform.rotation, _offset);

	_worldMatrix = Engine::Math::Matrix::CreateScale(0.4f)
		* Engine::Math::Matrix::CreateFromQuaternion(q)
		* Engine::Math::Matrix::CreateTranslation(_transform.position.x, _transform.position.y, _transform.position.z);

	UpdateState();
}

void Remote::PostAttach()
{
	Object::PostAttach();
}

void Remote::UpdateState()
{
	// Jump
	if (_bitFlag->IsOnFlag(StateFlag::Jump_Started))
	{
		if (_animator->IsLastFrame(0.9f))
		{
			if (!_bitFlag->IsOnFlag(StateFlag::Jump_Triggered))
			{
				_sync->_jump.set_power(15.f);
				_sync->_jump.SerializeToString(&_sync->_msgBuffer);

				Engine::Application::GetNetworkManager()->SaveSendData(
					(short)PacketID::Jump,
					_sync->_msgBuffer,
					_sync->_jump.ByteSizeLong(),
					_sync->GetSerialNumber()
				);

				_bitFlag->OnFlag(StateFlag::Jump_Triggered);
				_animator->ChangeAnimation("rig|Anim_Jump_loop");
				_animator->SetAnimationSpeed(1.f);
			}
		}
		if (_animator->IsLastFrame(0.3f))
		{
			if (_bitFlag->IsOnFlag(StateFlag::Jump_Triggered))
			{
				_bitFlag->OffFlag(StateFlag::Jump | StateFlag::Jump_Started | StateFlag::Jump_Triggered);
				_animator->ChangeAnimation("rig|Anim_Jump_end");
			}
		}
	}

	if (!_bitFlag->IsOnFlag(StateFlag::Walk | StateFlag::Jump | StateFlag::Interact))
	{
		if (_animator->IsLastFrame(0.1f))
		{
			_animator->ChangeAnimation("rig|Anim_Idle");
		}
	}

	if (_bitFlag->IsOnFlag(StateFlag::Interact_Started))
	{
		if (_animator->IsLastFrame(0.1f))
		{
			_animator->ChangeAnimation("rig|Anim_Interaction_loop");
			_bitFlag->OffFlag(StateFlag::Interact_Started);
		}
	}
}

void Remote::SetSerialNumber(int num)
{
	_sync->SetSerialNumber(num);
}

const int Remote::GetSerialNumber() const
{
	return _sync->GetSerialNumber();
}

void Remote::StateChange(const MoveMsg::StateChange* msg)
{
	unsigned long long flag = msg->stateinfo();
	
	if (flag == _bitFlag->GetCurrentFlag())
		return;

	if (!_bitFlag->IsOnFlag(StateFlag::Jump))
	{
		if (_bitFlag->IsOnFlag(StateFlag::Interact))
		{
			unsigned long long checkFlag = flag & (StateFlag::Interact | 
												   StateFlag::Interact_Started | 
												   StateFlag::Interact_Triggered);
			if (0 == flag)
			{
				_animator->ChangeAnimation("rig|Anim_Interaction_end");
			}
		}
		else
		{			
			if (flag & StateFlag::Walk)
			{
				_animator->ChangeAnimation("rig|Anim_Walk");
			}
			else
			{
				_animator->ChangeAnimation("rig|Anim_Idle");
			}

			if (flag & StateFlag::Jump_Started)
			{
				_animator->ChangeAnimation("rig|Anim_Jump_start");
				_animator->SetAnimationSpeed(1.5f);
			}
		}

		if (!_bitFlag->IsOnFlag(StateFlag::Interact))
		{
			if (flag & StateFlag::Interact_Started)
			{
				_animator->ChangeAnimation("rig|Anim_Interaction_start");
				printf("interaction_start\n");
			}
		}
	}	

	_bitFlag->SetFlag(flag);
}

void Remote::SyncMove(const MoveMsg::MoveSync* msg)
{
	const auto& pos = msg->position();
	float x = *(pos.begin());
	float y = *(pos.begin() + 1);
	float z = *(pos.begin() + 2);
	Engine::Math::Vector3 nextLocation(x, y, z);
	_remote->SetNextLocation(nextLocation);
	const auto& rot = msg->rotation();
	x = *(rot.begin());
	y = *(rot.begin() + 1);
	z = *(rot.begin() + 2);
	float w = *(rot.begin() + 3);
	_transform.rotation = Engine::Math::Quaternion(x, y, z, w);
}

void Remote::SetLocation(const MoveMsg::MoveSync* msg)
{
	const auto& pos = msg->position();
	float x = *(pos.begin());
	float y = *(pos.begin() + 1);
	float z = *(pos.begin() + 2);
	_transform.position = Engine::Math::Vector3(x, y, z);
}
