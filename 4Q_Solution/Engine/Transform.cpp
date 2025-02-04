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
