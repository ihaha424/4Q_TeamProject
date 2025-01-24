#include "pch.h"
#include "Vector4.h"

const Engine::Math::Vector4 Engine::Math::Vector4::Zero = Vector4{ 0.f, 0.f, 0.f };
const Engine::Math::Vector4 Engine::Math::Vector4::One = Vector4{ 1.f, 1.f, 1.f };

Engine::Math::Vector4::Vector4(const float x, const float y, const float z) :
	x(x), y(y), z(z)
{
}

Engine::Math::Vector4& Engine::Math::Vector4::operator+=(const Vector4& rhs) noexcept
{
	x += rhs.x;
	y += rhs.y;
	z += rhs.z;
	return *this;
}

Engine::Math::Vector4 Engine::Math::Vector4::operator*(const float scalar) const noexcept
{
	return Vector4{ x * scalar, y * scalar, z * scalar };
}

Engine::Math::Vector4::Vector4(const Input::Value& value) noexcept
{
	x = value.x;
	y = value.y;
	z = value.z;
}
