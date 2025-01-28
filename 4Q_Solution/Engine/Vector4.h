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

		Vector4(float x = 0.f, float y = 0.f, float z = 0.f, float w = 0.f) noexcept;
		Vector4(DirectX::SimpleMath::Vector4 vector) noexcept;
		Vector4(const PhysicsEngineAPI::Utils::Math::Vector4& value) noexcept;

		Vector4& operator=(const DirectX::SimpleMath::Vector4& vector) noexcept;
		Vector4& operator=(const PhysicsEngineAPI::Utils::Math::Vector4& value) noexcept;
	};
}
