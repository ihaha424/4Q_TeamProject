#include "pch.h"
#include "Player.h"

Player::Player() :
	_camera(L"MainCamera", 1.f, 1000.f, { 16,9 }, 3.141592f / 4) // TODO: Remove this.
	//, _staticMesh(L"../Resources/FBX/char.fbx")
	, _skeltalMesh(L"../Resources/Player/Player.X", &_worldMatrix)
	, _animator(&_skeltalMesh)
{
}

void Player::Addition()
{
	Object::Addition();
	AddComponent(&_movement);
	AddComponent(&_camera);
	//AddComponent(&_staticMesh);
	AddComponent(&_skeltalMesh);
	AddComponent(&_animator);
	AddComponent(&_tempLight);
}

void Player::PreInitialize()
{
	Object::PreInitialize();

	_movement.SetTarget(&_transform);

	const auto inputManager = Engine::Application::GetInputManager();
	Engine::Input::IMappingContext* mappingContext = nullptr;
	inputManager->GetMappingContext(L"Default", &mappingContext);
	Engine::Input::IAction* action = nullptr;
	mappingContext->GetAction(L"Move", &action);
	action->AddListener(Engine::Input::Trigger::Event::Triggered, [this](auto value)
	{
		_movement.SetDirection(value);
	});
	action->AddListener(Engine::Input::Trigger::Event::Started, [this](auto value)
		{
			_animator.ChangeAnimation("Run");
			//_animator.ChangeAnimation("Combo 1Shot", 1);
		});
	action->AddListener(Engine::Input::Trigger::Event::Completed, [this](auto value) { _animator.ChangeAnimation("Wait"); });
}

void Player::PostInitialize()
{
	_tempLight.SetType(Engine::Component::Light::Type::Directional);
	_tempLight.SetDiffuse(1.f, 1.f, 1.f, 1.f);
	_tempLight.SetDirection(0.f, 0.f, 1.f);
	_tempLight.SetIntensity(1.f);
	_tempLight.SetSpecular(1.f, 1.f, 1.f, 1.f);
	_tempLight.SetAmbient(0.2f, 0.2f, 0.2f, 0.2f);

	/*_animator.SetUpSplitBone(2);
	_animator.SplitBone(0, "Dummy_root");
	_animator.SplitBone(1, "Bip01-Spine1");*/
	_animator.ChangeAnimation("Wait");
	
	_worldMatrix = Engine::Math::Matrix::CreateScale(5.f, 5.f, 5.f);
}

void Player::PostAttach()
{
	Object::PostAttach();
	_camera.Activate();
}