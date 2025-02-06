#include "pch.h"
#include "Ray.h"

Ray::Ray(std::filesystem::path&& meshPath)
	: _meshPath(std::forward<std::filesystem::path>(meshPath))
	, _movement(nullptr)
	, _skeletalMesh(nullptr)
	, _animator(nullptr)
	, _camera(nullptr)
{
}

void Ray::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_movement = componentFactory->Clone<Engine::Component::Movement>(this);
	_camera = componentFactory->Clone<Engine::Component::Camera>(this);
	_skeletalMesh = componentFactory->Clone<Engine::Component::SkeletalMesh>(this);
	_animator = componentFactory->Clone<Engine::Component::Animator>(this);
	_rigid = componentFactory->Clone<Engine::Component::ChractorController>(this);
}

void Ray::SetCapsuleScale(Engine::Math::Vector3 capsuleScale)
{
	_capsuleScale = capsuleScale;
}

void Ray::DisposeComponents()
{
	_camera->Dispose();
	_movement->Dispose();
	_animator->Dispose();
	_skeletalMesh->Dispose();
	_rigid->Dispose();
}

void Ray::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);

	_camera->SetName(L"MainCamera");
	_movement->SetTarget(&_transform);

	_skeletalMesh->SetFilePath(_meshPath);
	_skeletalMesh->SetMatrix(&_worldMatrix);
	_animator->SetSkeletalMesh(_skeletalMesh);

	const auto inputManager = Engine::Application::GetInputManager();
	Engine::Input::IMappingContext* mappingContext = nullptr;
	inputManager->GetMappingContext(L"Default", &mappingContext);

	Engine::Input::IAction* moveAction = nullptr;
	mappingContext->GetAction(L"Move", &moveAction);
	moveAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](auto value)
		{
			Engine::Math::Vector3 direction = value;
			direction = Engine::Math::Vector3::TransformNormal(direction, _cameraParentMatrix);
			direction.y = 0.f;
			direction.Normalize();
			_transform.rotation = Engine::Math::Quaternion::CreateFromYawPitchRoll(Engine::Math::Vector3(0.f, _cameraRotation.y + 3.14f, 0.f));
			_rigid->_controller->SetDirection(direction);
			// _movement->SetDirection(direction);
		});
	moveAction->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value)
		{
			_animator->ChangeAnimation("rig|Anim_Walk");
		});
	moveAction->AddListener(Engine::Input::Trigger::Event::Completed, [this](auto value)
		{
			_animator->ChangeAnimation("rig|Anim_Idle");
			_rigid->_controller->SetDirection(Engine::Math::Vector3::Zero);
			//_movement->SetDirection(Engine::Math::Vector3::Zero);
		});

	Engine::Input::IAction* cameraAction = nullptr;
	mappingContext->GetAction(L"Camera", &cameraAction);
	cameraAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](Engine::Math::Vector3 value)
		{
			_cameraRotation += value;
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
}

void Ray::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	_movement->SetSpeed(100.f);

	//_skeltalMesh.SetRenderLayer(0);
	/*_animator.SetUpSplitBone(2);
	_animator.SplitBone(0, "Dummy_root");
	_animator.SplitBone(1, "Bip01-Spine1");
	_animator.ChangeAnimation("Wait");*/

	//_skeletalMesh->SetActiveShadow(false);
	_skeletalMesh->SetPostEffectFlag(1);
	_camera->SetParent(&_cameraParentMatrix);
}


void Ray::PostUpdate(float deltaTime)
{
	Object::PostUpdate(deltaTime);
	
	_worldMatrix = Engine::Math::Matrix::CreateScale(0.4f)
			     * Engine::Math::Matrix::CreateFromQuaternion(_transform.rotation)
				 * Engine::Math::Matrix::CreateTranslation(_transform.position.x, _transform.position.y, _transform.position.z);

	// Temp Shoulder View Camera;
	auto rotation = Engine::Math::Quaternion::CreateFromYawPitchRoll(_cameraRotation);
	_cameraParentMatrix = Engine::Math::Matrix::CreateFromQuaternion(rotation);	

	Engine::Math::Vector3 tempPostion = _transform.position;
	tempPostion.y += 50.f;
	tempPostion += _cameraParentMatrix.Backward() * -60.f;
	tempPostion += _cameraParentMatrix.Right() * 10.f;

	_cameraParentMatrix *= Engine::Math::Matrix::CreateTranslation(tempPostion);
}

void Ray::PostAttach()
{
	Object::PostAttach();
	_camera->Activate();
}
