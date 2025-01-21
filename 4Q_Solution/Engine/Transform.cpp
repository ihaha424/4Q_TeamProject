#include "pch.h"
#include "Transform.h"

Engine::Transform::Transform() :
	position(Math::Vector3::Zero),
	rotation(Math::Quaternion::Identity),
	scale(Math::Vector3::One)
{
}

void Engine::Transform::Translate(const Math::Vector3 translation)
{
	position += translation;
}
