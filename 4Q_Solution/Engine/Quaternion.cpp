#include "pch.h"
#include "Quaternion.h"

Engine::Math::Quaternion::Quaternion(const DirectX::SimpleMath::Quaternion& quaternion) noexcept :
	DirectX::SimpleMath::Quaternion(quaternion)
{
}

Engine::Math::Quaternion& Engine::Math::Quaternion::operator=(const DirectX::SimpleMath::Quaternion& quaternion) noexcept
{
	DirectX::SimpleMath::Quaternion::operator=(quaternion);
	return *this;
}
