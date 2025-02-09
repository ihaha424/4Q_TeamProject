#include "pch.h"
#include "Player.h"
#include "GrabbedObject.h"
#include "InteractObject.h"

Player::Player() : 
	//, _movement(nullptr)
	_camera(nullptr)
	, _skeletalMesh(nullptr)
	, _animator(nullptr), _fixedArm(nullptr), _rigid(nullptr), _bitFlag(nullptr)
	, _offset(Engine::Math::Quaternion::CreateFromYawPitchRoll(std::numbers::pi_v<float>, 0, 0))
{
}

void Player::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	//_movement = componentFactory->Clone<Engine::Component::Movement>(this);
	_camera = componentFactory->Clone<Engine::Component::Camera>(this);
	_skeletalMesh = componentFactory->Clone<Engine::Component::SkeletalMesh>(this);
	_animator = componentFactory->Clone<Engine::Component::Animator>(this);
	_rigid = componentFactory->Clone<Engine::Component::ChractorController>(this);
	_fixedArm = componentFactory->Clone<Engine::Component::FixedArm>(this);
	_remote = componentFactory->Clone<RemoteMove>(this);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
	_bitFlag = componentFactory->Clone<Engine::Component::BitFlag>(this);
}

void Player::SetCapsuleScale(Engine::Math::Vector3 capsuleScale)
{
	_capsuleScale = capsuleScale;
}

void Player::DisposeComponents()
{
	_camera->Dispose();
	//_movement->Dispose();
	_animator->Dispose();
	_skeletalMesh->Dispose();
	_rigid->Dispose();
	_fixedArm->Dispose();
	_remote->Dispose();
	_sync->Dispose();
	_bitFlag->Dispose();
}

void Player::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);

	_camera->SetName(L"MainCamera");
	//_movement->SetTarget(&_transform);

	_skeletalMesh->SetFilePath(_meshPath);
	_skeletalMesh->SetMatrix(&_worldMatrix);
	_animator->SetSkeletalMesh(_skeletalMesh);

	// FixedArm
	_fixedArm->SetTarget(&_transform);
	_fixedArm->SetCameraComponent(_camera);
	_fixedArm->SetDistance(150.f);
	_fixedArm->SetCameraPosition(Engine::Math::Vector2{ 0.f, 60.f });
	_fixedArm->SetRotationSpeed(Engine::Math::Vector2{ 0.02f, 0.04f });
	_fixedArm->SetFollowSpeed(0.01f);

	_remote->SetTarget(&_transform);

	const auto inputManager = Engine::Application::GetInputManager();
	Engine::Input::IMappingContext* mappingContext = nullptr;
	inputManager->GetMappingContext(L"Default", &mappingContext);

	Engine::Input::IAction* cameraAction = nullptr;
	mappingContext->GetAction(L"Camera", &cameraAction);
	cameraAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](Engine::Math::Vector3 value)
		{ _fixedArm->Rotate(value); });

	Engine::Input::IAction* moveAction = nullptr;
	mappingContext->GetAction(L"Move", &moveAction);
	moveAction->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value) { MoveStarted(); });
	moveAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](auto value) { MoveTriggered(value); });
	moveAction->AddListener(Engine::Input::Trigger::Event::Completed, [this](auto value) { MoveCompleted(); });

	Engine::Input::IAction* jumpAction = nullptr;
	mappingContext->GetAction(L"Jump", &jumpAction);
	jumpAction->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value) { JumpStarted(); });

	Engine::Input::IAction* interactAction = nullptr;
	mappingContext->GetAction(L"Interact", &interactAction);
	interactAction->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value) { InteractStarted(); });
	interactAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](auto value) { InteractTriggered(); });
	interactAction->AddListener(Engine::Input::Trigger::Event::Completed, [this](auto value) { InteractCompleted(); });

	auto PhysicsManager = Engine::Application::GetPhysicsManager();

	Engine::Physics::ControllerDesc cd;
	cd.position = Engine::Math::Vector3(0.f, 0.f, 0.f);
	cd.height = 100.f;
	cd.radius = 20.f;
	// TODO: Player Gravity
	//cd.gravity = { 0.f, -9.8f, 0.f };
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

	_sync->AddCallback((short)PacketID::MoveSync, &Player::SyncMove, this);
	_sync->AddCallback((short)PacketID::DataRemote, &Player::SetLocation, this);
}

void Player::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	//_movement->SetSpeed(100.f);
	_speed = 100.f;
	_remote->SetSpeed(_speed);

	//_skeltalMesh.SetRenderLayer(0);
	/*_animator.SetUpSplitBone(2);
	_animator.SplitBone(0, "Dummy_root");
	_animator.SplitBone(1, "Bip01-Spine1");
	_animator.ChangeAnimation("Wait");*/

	//_skeletalMesh->SetActiveShadow(false);
	_skeletalMesh->SetPostEffectFlag(1);
}


void Player::PostUpdate(float deltaTime)
{
	Object::PostUpdate(deltaTime);

	Engine::Math::Quaternion q = Engine::Math::Quaternion::Concatenate(_transform.rotation, _offset);

	_worldMatrix = Engine::Math::Matrix::CreateScale(0.4f)
		* Engine::Math::Matrix::CreateFromQuaternion(q)
		* Engine::Math::Matrix::CreateTranslation(_transform.position.x, _transform.position.y, _transform.position.z);

	UpdateState();
}

void Player::PostAttach()
{
	Object::PostAttach();
	_camera->Activate();
}

void Player::MoveStarted()
{
	_bitFlag->OnFlag(StateFlag::Walk);
	SendStateMessage();
}

void Player::MoveTriggered(Engine::Math::Vector3 value)
{
	if (!_bitFlag->IsOnFlag(StateFlag::Jump))
		_animator->ChangeAnimation("rig|Anim_Walk");

	_remote->SetDirection(_fixedArm->GetTransformDirection(value));
	_transform.rotation = _fixedArm->GetRotation(value, _transform.rotation);
	//_fixedArm->FollowDirection(value);

	Engine::Math::Vector3 direction = _fixedArm->GetTransformDirection(value);
	_sync->_move.set_x(direction.x);
	_sync->_move.set_y(direction.y);
	_sync->_move.set_z(direction.z);
	_sync->_move.add_rotation(_transform.rotation.x);
	_sync->_move.add_rotation(_transform.rotation.y);
	_sync->_move.add_rotation(_transform.rotation.z);
	_sync->_move.add_rotation(_transform.rotation.w);
	_sync->_move.set_speed(_remote->GetSpeed());

	_sync->_move.SerializeToString(&_sync->_msgBuffer);

	Engine::Application::GetNetworkManager()->SaveSendData(
		(short)PacketID::Move,
		_sync->_msgBuffer,
		_sync->_move.ByteSizeLong(),
		_sync->GetSerialNumber()
	);
	_sync->_move.Clear();
}

void Player::MoveCompleted()
{
	if (!_bitFlag->IsOnFlag(StateFlag::Jump | StateFlag::Interact))
		_animator->ChangeAnimation("rig|Anim_Idle");

	_bitFlag->OffFlag(StateFlag::Walk);

	_remote->SetDirection(Engine::Math::Vector3::Zero);

	_sync->_move.set_x(0);
	_sync->_move.set_y(0);
	_sync->_move.set_z(0);
	_sync->_move.set_speed(0);

	_sync->_move.SerializeToString(&_sync->_msgBuffer);

	Engine::Application::GetNetworkManager()->SaveSendData(
		(short)PacketID::Move,
		_sync->_msgBuffer,
		_sync->_move.ByteSizeLong(),
		_sync->GetSerialNumber()
	);

	SendStateMessage();
}

void Player::JumpStarted()
{
	if (_bitFlag->IsOnFlag(StateFlag::Jump))
		return;

	_bitFlag->OnFlag(StateFlag::Jump | StateFlag::Jump_Started);
	_animator->ChangeAnimation("rig|Anim_Jump_start");
	_animator->SetAnimationSpeed(1.5f);
	SendStateMessage();
}

void Player::InteractStarted()
{
	if (_bitFlag->IsOnFlag(StateFlag::Interact))
		return;

	/*Raycast*/
	{
		Engine::Physics::AdditionalQueryData queryData;
		auto PhysicsManager = Engine::Application::GetPhysicsManager();
		auto raycastScene = PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene));
		auto rayDirection = _transform.GetForward();	// WHy????????? I don't konw Why flip the X-axis
		rayDirection.x *= -1;
		raycastScene->Raycast(queryData, _transform.position, rayDirection, 1000.f);
		if (queryData.num > 0)
		{
			for (size_t i = 0; i < queryData.num; i++)
			{
				Engine::Object* obj = static_cast<Engine::Object*>(queryData.UserDatas[i]->GetOwner());
				auto interactObject = dynamic_cast<InteractObject*>(obj);
				if (nullptr != interactObject)
				{
					interactObject->Interact();
				}
				//Picking
				auto checkGrabbedObject = dynamic_cast<GrabbedObject*>(obj);
				if (nullptr != checkGrabbedObject)
				{
					bool isGrab = checkGrabbedObject->Grabbed(&_transform);
					grabbedObject = checkGrabbedObject;
					continue;
				}
			}
		}
	}

	_bitFlag->OnFlag(StateFlag::Interact | StateFlag::Interact_Started);
	_animator->ChangeAnimation("rig|Anim_Interaction_start");
	SendStateMessage();
}

void Player::InteractTriggered()
{
	if (_bitFlag->IsOnFlag(StateFlag::Interact_Started))
	{
		if (_animator->IsLastFrame(0.1f))
		{
			_bitFlag->OffFlag(StateFlag::Interact_Started);
			_bitFlag->OnFlag(StateFlag::Interact_Triggered);
			_animator->ChangeAnimation("rig|Anim_Interaction_loop");
		}
	}
}

void Player::InteractCompleted()
{
	_animator->ChangeAnimation("rig|Anim_Interaction_end");
	_bitFlag->OffFlag(StateFlag::Interact | StateFlag::Interact_Started | StateFlag::Interact_Triggered);
	SendStateMessage();

	// Put
	{
		if (nullptr != grabbedObject)
		{
			grabbedObject->PutThis();
			grabbedObject = nullptr;
		}
	}
}

void Player::SendStateMessage()
{
	_sync->_stateChange.set_stateinfo(_bitFlag->GetCurrentFlag());
	_sync->_stateChange.SerializeToString(&_sync->_msgBuffer);

	Engine::Application::GetNetworkManager()->SaveSendData(
		(short)PacketID::StateChange,
		_sync->_msgBuffer,
		_sync->_stateChange.ByteSizeLong(),
		_sync->GetSerialNumber()
	);
}

void Player::UpdateState()
{
	// Jump
	if (_bitFlag->IsOnFlag(StateFlag::Jump_Started))
	{
		if (_animator->IsLastFrame(0.9f))
		{
			if (!_bitFlag->IsOnFlag(StateFlag::Jump_Triggered))
			{
				_remote->SetSpeed(_speed * 0.5f);
				_remote->SetDirection(Engine::Math::Vector3(0.f, 1.f, 0.f));

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
				_remote->SetDirection(Engine::Math::Vector3::Zero);
			}
		}
	}

	if (!_bitFlag->IsOnFlag(StateFlag::Walk | StateFlag::Jump | StateFlag::Interact))
	{
		if (_animator->IsLastFrame(0.1f))
		{
			_animator->ChangeAnimation("rig|Anim_Idle");
			_remote->SetSpeed(_speed);
		}
	}
}

void Player::SetSerialNumber(int num)
{
	_sync->SetSerialNumber(num);
}

const int Player::GetSerialNumber() const
{
	return _sync->GetSerialNumber();
}

void Player::SyncMove(const MoveMsg::MoveSync* msg)
{
	float x = msg->x();
	float y = msg->y();
	float z = msg->z();
	Engine::Math::Vector3 nextLocation(x, y, z);
	_remote->SetNextLocation(nextLocation);
}

void Player::SetLocation(const MoveMsg::MoveSync* msg)
{
	float x = msg->x();
	float y = msg->y();
	float z = msg->z();
	_transform.position = Engine::Math::Vector3(x, y, z);
}
