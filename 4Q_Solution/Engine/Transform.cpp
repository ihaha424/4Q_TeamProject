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
