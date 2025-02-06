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
		});
	moveAction->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value)
		{
			_animator->ChangeAnimation("rig|Anim_Walk");
		});
	moveAction->AddListener(Engine::Input::Trigger::Event::Completed, [this](auto value)
		{
			_animator->ChangeAnimation("rig|Anim_Idle");
			//_movement->SetDirection(Engine::Math::Vector3::Zero);
			_remote->SetDirection(Engine::Math::Vector3::Zero);
		});

	Engine::Input::IAction* cameraAction = nullptr;
	mappingContext->GetAction(L"Camera", &cameraAction);
	cameraAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](Engine::Math::Vector3 value)
		{
			_fixedArm->Rotate(value);
		});


	auto PhysicsManager = Engine::Application::GetPhysicsManager();

	Engine::Physics::ControllerDesc cd;
	cd.position = Engine::Math::Vector3(400, 400, 400);
	cd.height = 10.f;
	cd.radius = 2.f;
	// TODO: Player Gravity
	//cd.gravity = { 0.f, -9.8f, 0.f };
	cd.contactOffset = 0.001f;
	cd.stepOffset = 1.f;
	cd.slopeLimit = 0.707f;

	Engine::Physics::IController* controller;
	PhysicsManager->CreatePlayerController(&controller, PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene)), cd);
	_rigid->_controller = static_cast<Engine::Physics::Controller*>(controller);
	// TODO: 적용해보고 속성값 조절
	// _rigid->_controller->SetBottomPosition({ 0,10,0 });

	// TODO: Camera Scene에 추가
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
