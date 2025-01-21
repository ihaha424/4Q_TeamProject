#include "pch.h"
#include "Vector3.h"

const Engine::Math::Vector3 Engine::Math::Vector3::Zero = Vector3{ 0.f, 0.f, 0.f };
const Engine::Math::Vector3 Engine::Math::Vector3::One = Vector3{ 1.f, 1.f, 1.f };

Engine::Math::Vector3::Vector3(const float x, const float y, const float z) :
	x(x), y(y), z(z)
{
}

Engine::Math::Vector3& Engine::Math::Vector3::operator+=(const Vector3& rhs) noexcept
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Engine::Math::Vector3 Engine::Math::Vector3::operator*(const float scalar) const noexcept
{
	return Vector3{ x * scalar, y * scalar, z * scalar };
}

Engine::Math::Vector3::Vector3(const Input::Value& value) noexcept
{
	x = value.x;
	y = value.y;
	z = value.z;
}
