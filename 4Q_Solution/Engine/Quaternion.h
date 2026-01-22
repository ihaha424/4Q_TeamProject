#pragma once

namespace PhysicsEngineAPI::Utils::Math
{
	union Vector4;
}

namespace Engine::Math
{
	struct Quaternion : DirectX::SimpleMath::Quaternion
	{
		using DirectX::SimpleMath::Quaternion::Identity;

		Quaternion() noexcept = default;
		Quaternion(float x, float y, float z, float w) noexcept;
		Quaternion(const DirectX::SimpleMath::Quaternion& quaternion) noexcept;
		Quaternion(const PhysicsEngineAPI::Utils::Math::Vector4& value) noexcept;

		Quaternion& operator=(const DirectX::SimpleMath::Quaternion& quaternion) noexcept;
		Quaternion& operator=(const PhysicsEngineAPI::Utils::Math::Vector4& value) noexcept;
	};
}