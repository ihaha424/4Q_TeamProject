#include "pch.h"
#include "Vector3.h"

const Engine::Math::Vector3 Engine::Math::Vector3::Zero = Engine::Math::Vector3{ 0.f, 0.f, 0.f };

Engine::Math::Vector3::Vector3(const float x, const float y, const float z) :
	x(x), y(y), z(z)
{
}

Engine::Math::Vector3::Vector3(const DSH::Input::Value value) noexcept
{
	x = value.x;
	y = value.y;
	z = value.z;
}
