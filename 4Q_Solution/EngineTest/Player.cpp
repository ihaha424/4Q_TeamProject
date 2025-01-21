#include "pch.h"
#include "Player.h"

Player::Player() :
	_camera(L"MainCamera", 1.f, 1000.f, { 16,9 }, 3.141592f / 4) // TODO: Remove this.
	, _staticMesh(L"../Resources/FBX/char.fbx")
{
}

void Player::Addition()
{
	Object::Addition();
	AddComponent(&_movement);
	AddComponent(&_camera);
	AddComponent(&_staticMesh);
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
	action->AddListener(Engine::Input::Trigger::Event::Triggered, [this](auto value) { _movement.SetDirection(value); });	
}

void Player::PostInitialize()
{
	_tempLight.SetType(Engine::Component::Light::Type::Directional);
	_tempLight.SetDiffuse(1.f, 1.f, 1.f, 1.f);
	_tempLight.SetDirection(0.f, 0.f, 1.f);
	_tempLight.SetIntensity(1.f);
	_tempLight.SetSpecular(1.f, 1.f, 1.f, 1.f);
}

void Player::PostAttach()
{
	Object::PostAttach();
	_camera.Activate();
}