#include "pch.h"
#include "Transform.h"

Engine::Transform::Transform() :
	position(Math::Vector3::Zero),
	rotation(Math::Quaternion::Identity),
	scale(Math::Vector3::One)
{
}

Engine::Transform::Transform(Math::Vector3 _position, Math::Quaternion _rotation, Math::Vector3 _scale) :
	position(_position),
	rotation(_rotation),
	scale(_scale)
{
}

void Engine::Transform::Translate(const Math::Vector3 translation)
{
	position += translation;
}

Engine::Math::Matrix Engine::Transform::GetMatrix()
{
	Engine::Math::Matrix matrix;

	matrix = Engine::Math::Matrix::CreateScale(scale)
		* Engine::Math::Matrix::CreateFromQuaternion(rotation)
		* Engine::Math::Matrix::CreateTranslation(position);
	return matrix;
}
