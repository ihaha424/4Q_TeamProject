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
}

void Engine::Component::FixedArm::Update(const float deltaTime)
{
	Component::Update(deltaTime);
	_matrix = Math::Matrix::CreateFromYawPitchRoll(_rotation);

	Math::Vector3 tempPosition = _target->position;
	tempPosition += _matrix.Backward() * -_distance;
	tempPosition += _matrix.Up() * _cameraPosition.y;
	tempPosition += _matrix.Right() * _cameraPosition.x;

	_matrix *= Math::Matrix::CreateTranslation(tempPosition);
}

void Engine::Component::FixedArm::Rotate(const Math::Vector3& value)
{
	_rotation += value;
}

void Engine::Component::FixedArm::SetCameraPosition(const Math::Vector2& value)
{
	_cameraPosition = value;
}

Engine::Math::Vector3 Engine::Component::FixedArm::GetForward() const
{
	return _matrix.Forward();
}


