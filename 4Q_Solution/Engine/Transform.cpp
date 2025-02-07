#include "pch.h"
#include "Transform.h"

Engine::Transform::Transform() :
	position(Math::Vector3::Zero),
	rotation(Math::Quaternion::Identity),
	scale(Math::Vector3::One)
{
}

Engine::Transform::Transform(const Math::Vector3 position, const Math::Quaternion rotation, const Math::Vector3 scale) :
	position(position),
	rotation(rotation),
	scale(scale)
{
}

void Engine::Transform::Translate(const Math::Vector3 translation)
{
	position += translation;
}

Engine::Math::Vector3 Engine::Transform::GetForward() const
{
	return Math::Vector3::Transform(Math::Vector3::Forward, rotation);
}

Engine::Math::Vector3 Engine::Transform::GetRight() const
{
	return Math::Vector3::Transform(Math::Vector3::Right, rotation);
}

Engine::Math::Vector3 Engine::Transform::GetUp() const
{
	return Math::Vector3::Transform(Math::Vector3::Up, rotation);
}

Engine::Math::Vector3 Engine::Transform::GetBackward() const
{
	return Math::Vector3::Transform(Math::Vector3::Backward, rotation);
}

Engine::Math::Vector3 Engine::Transform::GetLeft() const
{
	return Math::Vector3::Transform(Math::Vector3::Left, rotation);
}

Engine::Math::Vector3 Engine::Transform::GetDown() const
{
	return Math::Vector3::Transform(Math::Vector3::Down, rotation);
}

Engine::Math::Matrix Engine::Transform::GetMatrix()
{
	Engine::Math::Matrix matrix;

	matrix = Engine::Math::Matrix::CreateScale(scale)
		* Engine::Math::Matrix::CreateFromQuaternion(rotation)
		* Engine::Math::Matrix::CreateTranslation(position);
	return matrix;
}
