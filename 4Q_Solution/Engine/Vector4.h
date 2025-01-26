#pragma once

namespace PhysicsEngineAPI::Utils::Math
{
	union Vector4;
}

namespace Engine::Math
{
	struct Vector4 : DirectX::SimpleMath::Vector4
	{
		using DirectX::SimpleMath::Vector4::Zero;
		using DirectX::SimpleMath::Vector4::One;

		Vector4(float x, float y, float z, float w) noexcept;
		Vector4(DirectX::SimpleMath::Vector4 vector) noexcept;
		Vector4(const PhysicsEngineAPI::Utils::Math::Vector4& value) noexcept;

		Vector4& operator=(const DirectX::SimpleMath::Vector4& vector) noexcept;
		Vector4& operator=(const PhysicsEngineAPI::Utils::Math::Vector4& value) noexcept;
	};
}
