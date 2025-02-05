#include "pch.h"
#include "FixedArm.h"

Engine::Component::FixedArm::FixedArm() : _target(nullptr), _camera(nullptr), _distance(200.0f)
{
}

void Engine::Component::FixedArm::SetDistance(const float distance)
{
	_distance = distance;
}

void Engine::Component::FixedArm::SetTarget(Transform* target)
{
	_target = target;
}

void Engine::Component::FixedArm::SetCameraComponent(Camera* camera)
{
	_camera = camera;
}

void Engine::Component::FixedArm::Initialize(const Modules& modules)
{
	Component::Initialize(modules);
	_camera->SetParent(&_matrix);
	_matrix = Math::Matrix::CreateTranslation(_target->GetBackward() * -_distance);
}

void Engine::Component::FixedArm::Update(const float deltaTime)
{
	Component::Update(deltaTime);

}
