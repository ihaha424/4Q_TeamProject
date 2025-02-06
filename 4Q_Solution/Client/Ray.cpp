#include "pch.h"
#include "Ray.h"

Ray::Ray(std::filesystem::path&& meshPath)
	: _meshPath(std::forward<std::filesystem::path>(meshPath))
	  //, _movement(nullptr)
	  , _camera(nullptr)
	  , _skeletalMesh(nullptr)
	  , _animator(nullptr), _fixedArm(nullptr), _rigid(nullptr),
_offset(Engine::Math::Quaternion::CreateFromYawPitchRoll(std::numbers::pi_v<float>,0, 0))
{
}

void Ray::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	//_movement = componentFactory->Clone<Engine::Component::Movement>(this);
	_camera = componentFactory->Clone<Engine::Component::Camera>(this);
	_skeletalMesh = componentFactory->Clone<Engine::Component::SkeletalMesh>(this);
	_animator = componentFactory->Clone<Engine::Component::Animator>(this);
	_rigid = componentFactory->Clone<Engine::Component::ChractorController>(this);
	_fixedArm = componentFactory->Clone<Engine::Component::FixedArm>(this);
	_remote = componentFactory->Clone<RemoteMove>(this);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
}

void Ray::SetCapsuleScale(Engine::Math::Vector3 capsuleScale)
{
	_capsuleScale = capsuleScale;
}

void Ray::DisposeComponents()
{
	_camera->Dispose();
	//_movement->Dispose();
	_animator->Dispose();
	_skeletalMesh->Dispose();
	_rigid->Dispose();
	_fixedArm->Dispose();
	_remote->Dispose();
	_sync->Dispose();
}

void Ray::PreInitialize(const Engine::Modules& modules)
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

	Engine::Input::IAction* moveAction = nullptr;
	mappingContext->GetAction(L"Move", &moveAction);
	moveAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](auto value)
		{
			//_movement->SetDirection(_fixedArm->GetTransformDirection(value));
			_remote->SetDirection(_fixedArm->GetTransformDirection(value));
			_transform.rotation = _fixedArm->GetRotation(value, _transform.rotation);
			_fixedArm->FollowDirection(value);

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


			//Engine::Math::Vector3 direction = value;
			//direction = Engine::Math::Vector3::TransformNormal(direction, _cameraParentMatrix);
			//direction.y = 0.f;
			//direction.Normalize();
			//_transform.rotation = Engine::Math::Quaternion::CreateFromYawPitchRoll(Engine::Math::Vector3(0.f, _cameraRotation.y + 3.14f, 0.f));
			//_rigid->_controller->SetDirection(direction);
			//// _movement->SetDirection(direction);
		});
	moveAction->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value)
		{
			_animator->ChangeAnimation("rig|Anim_Walk");

			_sync->_stateChange.set_stateinfo(1);
			_sync->_stateChange.SerializeToString(&_sync->_msgBuffer);

			Engine::Application::GetNetworkManager()->SaveSendData(
				(short)PacketID::StateChange,
				_sync->_msgBuffer,
				_sync->_stateChange.ByteSizeLong(),
				_sync->GetSerialNumber()
			);
		});
	moveAction->AddListener(Engine::Input::Trigger::Event::Completed, [this](auto value)
		{
			_animator->ChangeAnimation("rig|Anim_Idle");
			//_movement->SetDirection(Engine::Math::Vector3::Zero);
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

			_sync->_stateChange.set_stateinfo(0);
			_sync->_stateChange.SerializeToString(&_sync->_msgBuffer);

			Engine::Application::GetNetworkManager()->SaveSendData(
				(short)PacketID::StateChange,
				_sync->_msgBuffer,
				_sync->_stateChange.ByteSizeLong(),
				_sync->GetSerialNumber()
			);

			// _rigid->_controller->SetDirection(Engine::Math::Vector3::Zero);
			//_movement->SetDirection(Engine::Math::Vector3::Zero);
		});

	Engine::Input::IAction* cameraAction = nullptr;
	mappingContext->GetAction(L"Camera", &cameraAction);
	cameraAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](Engine::Math::Vector3 value)
		{
			_fixedArm->Rotate(value);
		});

	Engine::Input::IAction* jumpAction = nullptr;
	mappingContext->GetAction(L"Jump", &jumpAction);
	jumpAction->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value)
		{
			_transform.position.y += 100.f;
		});

	Engine::Input::IAction* interactAction = nullptr;
	mappingContext->GetAction(L"Interact", &interactAction);
	interactAction->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value)
		{
			_transform.position.y -= 100.f;
		});

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

	_rigid->_controller->SetMoveSpeed(1000.f);

	// TODO: 적용해보고 속성값 조절
	// _rigid->_controller->SetBottomPosition({ 0,10,0 });

	// TODO: Camera Scene에 추가

	_sync->AddCallback((short)PacketID::MoveSync, &Ray::SyncMove, this);
	_sync->AddCallback((short)PacketID::DataRemote, &Ray::SetLocation, this);
}

void Ray::PostInitialize(const Engine::Modules& modules)
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


void Ray::PostUpdate(float deltaTime)
{
	Object::PostUpdate(deltaTime);

	Engine::Math::Quaternion q = Engine::Math::Quaternion::Concatenate(_transform.rotation, _offset);
	
	_worldMatrix = Engine::Math::Matrix::CreateScale(0.4f)
			     * Engine::Math::Matrix::CreateFromQuaternion(q)
				 * Engine::Math::Matrix::CreateTranslation(_transform.position.x, _transform.position.y, _transform.position.z);
}

void Ray::PostAttach()
{
	Object::PostAttach();
	_camera->Activate();
}

void Ray::SetSerialNumber(int num)
{
	_sync->SetSerialNumber(num);
}

const int Ray::GetSerialNumber() const
{
	return _sync->GetSerialNumber();
}

void Ray::SyncMove(const MoveMsg::MoveSync* msg)
{
	float x = msg->x();
	float y = msg->y();
	float z = msg->z();
	Engine::Math::Vector3 nextLocation(x, y, z);
	_remote->SetNextLocation(nextLocation);
}

void Ray::SetLocation(const MoveMsg::MoveSync* msg)
{
	float x = msg->x();
	float y = msg->y();
	float z = msg->z();
	_transform.position = Engine::Math::Vector3(x, y, z);
}
