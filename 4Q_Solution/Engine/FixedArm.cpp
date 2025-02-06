#include "pch.h"
#include "FixedArm.h"

#include "../Client/Application.h"

Engine::Component::FixedArm::FixedArm() :
	_target(nullptr), _camera(nullptr), _distance(200.0f), _rotationSpeed(Math::Vector2::One),
_followSpeed(0.01f)
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
	_rotation += value.Split(_rotationSpeed);
}

void Engine::Component::FixedArm::SetCameraPosition(const Math::Vector2& value)
{
	_cameraPosition = value;
}

void Engine::Component::FixedArm::SetRotationSpeed(const Math::Vector2& speed)
{
	_rotationSpeed = speed;
}

Engine::Math::Vector3 Engine::Component::FixedArm::GetForward() const
{
	return _matrix.Forward();
}

Engine::Math::Vector3 Engine::Component::FixedArm::GetTransformDirection(const Math::Vector3& direction) const
{
	auto result = Math::Vector3::TransformNormal(direction, _matrix);
	result.y = 0.f;
	result.Normalize();
	return result;
}

Engine::Math::Quaternion Engine::Component::FixedArm::GetForwardRotation() const
{
	return Math::Quaternion::CreateFromYawPitchRoll({ 0,_rotation.y,0 });
}

Engine::Math::Quaternion Engine::Component::FixedArm::GetRotation(const Math::Vector3& direction) const
{
	auto result = Math::Vector3::TransformNormal(direction, _matrix);
	result.y = 0.f;
	result.Normalize();
	return Math::Quaternion::CreateFromYawPitchRoll({ 0, std::atan2(result.x, result.z),0 });
}

Engine::Math::Quaternion Engine::Component::FixedArm::GetRotation(const Math::Vector3& direction,
	const Math::Quaternion& rotation) const
{
	auto beforeForward = Math::Vector3::Transform(Math::Vector3::Forward, rotation);
	beforeForward.Normalize();

	auto afterForward = Math::Vector3::TransformNormal(direction, _matrix);
	afterForward.y = 0.f;
	afterForward.Normalize();

	const float start = rotation.ToEuler().y;
	const float end = std::atan2(afterForward.x, afterForward.z);

	float delta = end - start;
	delta = std::fmod(delta + std::numbers::pi_v<float>, std::numbers::pi_v<float> * 2.f) - std::numbers::pi_v<float>;
	if (std::abs(delta) > std::numbers::pi_v<float>) delta -= std::numbers::pi_v<float> *2.f * (delta > 0 ? 1 : -1);

	float current = std::lerp(start, start + delta, 0.1f);

	return Math::Quaternion::CreateFromYawPitchRoll({ 0, current,0 });
}

void Engine::Component::FixedArm::FollowDirection(const Math::Vector3& direction)
{
	auto transformDirection = Math::Vector3::TransformNormal(direction, _matrix);
	transformDirection.y = 0.f;
	transformDirection.Normalize();
	auto cameraDirection = GetForward();
	cameraDirection.y = 0.f;
	cameraDirection.Normalize();
	const auto upVector = cameraDirection.Cross(transformDirection);
	_rotation.y -= upVector.y * _followSpeed;
}

void Engine::Component::FixedArm::SetFollowSpeed(const float speed)
{
	_followSpeed = speed;
}
