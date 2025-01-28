#include "pch.h"
#include "Quaternion.h"

Engine::Math::Quaternion::Quaternion(const DirectX::SimpleMath::Quaternion& quaternion) noexcept :
	DirectX::SimpleMath::Quaternion(quaternion)
{
}

Engine::Math::Quaternion::Quaternion(const PhysicsEngineAPI::Utils::Math::Vector4& value) noexcept :
	DirectX::SimpleMath::Quaternion(value.value)
{
}

Engine::Math::Quaternion& Engine::Math::Quaternion::operator=(const DirectX::SimpleMath::Quaternion& quaternion) noexcept
{
	DirectX::SimpleMath::Quaternion::operator=(quaternion);
	return *this;
}

Engine::Math::Quaternion& Engine::Math::Quaternion::operator=(const PhysicsEngineAPI::Utils::Math::Vector4& value) noexcept
{
	DirectX::SimpleMath::Quaternion::operator=(Quaternion(value));
	return *this;
}

