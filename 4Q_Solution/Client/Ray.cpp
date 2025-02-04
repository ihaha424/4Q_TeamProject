#include "pch.h"
#include "Ray.h"

Ray::Ray(std::filesystem::path&& meshPath)
	: _meshPath(std::forward<std::filesystem::path>(meshPath))
	, _movement(nullptr)
	, _skeletalMesh(nullptr)
	, _animator(nullptr)
	, _animationFSM(nullptr)
{
}

void Ray::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_movement = componentFactory->Clone<Engine::Component::Movement>(this);
	_skeletalMesh = componentFactory->Clone<Engine::Component::SkeletalMesh>(this);
	_animator = componentFactory->Clone<Engine::Component::Animator>(this);
	_animationFSM = componentFactory->Clone<Engine::Component::FiniteStateMachine>(this);
}

void Ray::DisposeComponents()
{
	_movement->Dispose();
	_animator->Dispose();
	_skeletalMesh->Dispose();
}

void Ray::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);

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
			direction = Engine::Math::Vector3::TransformNormal(direction, _worldMatrix);
			_movement->SetDirection(-direction);
		});
	moveAction->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value)
		{
			_animator->ChangeAnimation("rig|Anim_Walk");
		});
	moveAction->AddListener(Engine::Input::Trigger::Event::Completed, [this](auto value)
		{
			_animator->ChangeAnimation("rig|Anim_Idle");
			_movement->SetDirection(Engine::Math::Vector3::Zero);
		});
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
}


void Ray::PostUpdate(float deltaTime)
{
	Object::PostUpdate(deltaTime);

	_worldMatrix = Engine::Math::Matrix::CreateScale(0.4f)
				 * Engine::Math::Matrix::CreateFromQuaternion(_transform.rotation)
				 * Engine::Math::Matrix::CreateTranslation(_transform.position.x, _transform.position.y, _transform.position.z);
}