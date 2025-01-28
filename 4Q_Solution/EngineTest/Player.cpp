#include "pch.h"
#include "Player.h"

Player::Player(std::filesystem::path&& meshPath, std::filesystem::path&& fontPath) :
	_meshPath(std::forward<std::filesystem::path>(meshPath)),
	_fontPath(std::forward<std::filesystem::path>(fontPath)), _movement(nullptr),
	_camera(nullptr), _staticMesh(nullptr), _textRenderer(nullptr)
	//, _skeltalMesh(L"../Resources/Player/Player.X", &_worldMatrix)
	//, _animator(&_skeltalMesh)
{
}

void Player::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_movement = componentFactory->Clone<Engine::Component::MovementComponent>();
	_camera = componentFactory->Clone<Engine::Component::CameraComponent>();
	_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>();
	_textRenderer = componentFactory->Clone<Engine::Component::TextRenderer>();
}

void Player::DisposeComponents()
{
	_textRenderer->Dispose();
	_staticMesh->Dispose();
	_camera->Dispose();
	_movement->Dispose();
}

void Player::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_camera->SetName(L"MainCamera");
	_movement->SetTarget(&_transform);
	_staticMesh->SetFilePath(_meshPath);
	_staticMesh->SetMatrix(&_worldMatrix);
	_textRenderer->SetFontPath(_fontPath);

	const auto inputManager = Engine::Application::GetInputManager();
	Engine::Input::IMappingContext* mappingContext = nullptr;
	inputManager->GetMappingContext(L"Default", &mappingContext);

	Engine::Input::IAction* moveAction = nullptr;
	mappingContext->GetAction(L"Move", &moveAction);
	moveAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](auto value)
	{
		_movement->SetDirection(value);		
	});
	moveAction->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value) { /*_animator.ChangeAnimation("Run");*/ });
	moveAction->AddListener(Engine::Input::Trigger::Event::Completed, [this](auto value)
	{ 
		//_animator.ChangeAnimation("Wait"); 
		_movement->SetDirection(Engine::Math::Vector3::Zero);
	});

	Engine::Input::IAction* cameraAction = nullptr;
	mappingContext->GetAction(L"Camera", &cameraAction);
	cameraAction->AddListener(Engine::Input::Trigger::Event::Triggered, [this](auto value)
	{
		_camera->Rotate(value);
	});
}

void Player::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	_movement->SetSpeed(100.f);	
	_textRenderer->SetPosition(100, 100.f);
	_textRenderer->SetText(L"진지한 궁서체\nHello World!");
	_textRenderer->SetFontColor(1.f, 0.f, 0.f, 1.f);

	//_skeltalMesh.SetRenderLayer(0);
	/*_animator.SetUpSplitBone(2);
	_animator.SplitBone(0, "Dummy_root");
	_animator.SplitBone(1, "Bip01-Spine1");
	_animator.ChangeAnimation("Wait");*/
}

void Player::PostAttach()
{
	Object::PostAttach();
	_camera->Activate();	
}

void Player::PostUpdate(const float deltaTime)
{
	Object::PostUpdate(deltaTime);
	_worldMatrix = Engine::Math::Matrix::CreateScale(1.f) * Engine::Math::Matrix::CreateTranslation(_transform.position.x, _transform.position.y, _transform.position.z);

	/*Engine::Math::Vector3 tempPostion = _transform.position;
	tempPostion.z -= 300.f;
	tempPostion.y += 300.f;
	_camera.SetPosition(tempPostion);
	_camera.SetRotation(Engine::Math::Vector3(45.f, 0.f, 0.f));*/
}

RemotePlayer::RemotePlayer(std::filesystem::path&& meshPath):
	_meshPath(std::forward<std::filesystem::path>(meshPath)), _skeletalMesh(nullptr), _animator(nullptr)
	, _worldMatrix(Engine::Math::Matrix::Identity)
{
}

void RemotePlayer::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_skeletalMesh = componentFactory->Clone<Engine::Component::SkeletalMesh>();
	_animator = componentFactory->Clone<Engine::Component::Animator>();
}

void RemotePlayer::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_skeletalMesh->SetFilePath(_meshPath);
	_skeletalMesh->SetMatrix(&_worldMatrix);
	_animator->SetSkeletalMesh(_skeletalMesh);
}