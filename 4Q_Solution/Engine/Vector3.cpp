#include "pch.h"
#include "Vector3.h"

Engine::Math::Vector3::Vector3(const float x, const float y, const float z) noexcept :
	DirectX::SimpleMath::Vector3(x, y, z)
{
}

Engine::Math::Vector3::Vector3(const DirectX::SimpleMath::Vector3 vector) noexcept :
	DirectX::SimpleMath::Vector3(vector)
{
}

Engine::Math::Vector3::Vector3(const Input::Value& value) noexcept :
	DirectX::SimpleMath::Vector3(value.x, value.y, value.z)
{
}

Engine::Math::Vector3& Engine::Math::Vector3::operator=(const DirectX::SimpleMath::Vector3& vector) noexcept
{
	DirectX::SimpleMath::Vector3::operator=(vector);
	return *this;
}

Engine::Math::Vector3& Engine::Math::Vector3::operator=(const Input::Value& value) noexcept
{
	DirectX::SimpleMath::Vector3::operator=(Vector3(value));
	return *this;
}
