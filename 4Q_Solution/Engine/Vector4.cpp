#include "pch.h"
#include "Vector4.h"

Engine::Math::Vector4::Vector4(const float x, const float y, const float z, const float w) noexcept :
	DirectX::SimpleMath::Vector4(x, y, z, w)
{
}

Engine::Math::Vector4::Vector4(const DirectX::SimpleMath::Vector4 vector) noexcept :
	DirectX::SimpleMath::Vector4(vector)
{
}

Engine::Math::Vector4::Vector4(const PhysicsEngineAPI::Utils::Math::Vector4& value) noexcept :
	DirectX::SimpleMath::Vector4(value.value)
{
}

Engine::Math::Vector4& Engine::Math::Vector4::operator=(const DirectX::SimpleMath::Vector4& vector) noexcept
{
	DirectX::SimpleMath::Vector4::operator=(vector);
	return *this;
}

Engine::Math::Vector4& Engine::Math::Vector4::operator=(const PhysicsEngineAPI::Utils::Math::Vector4& value) noexcept
{
	DirectX::SimpleMath::Vector4::operator=(Vector4(value));
	return *this;
}



