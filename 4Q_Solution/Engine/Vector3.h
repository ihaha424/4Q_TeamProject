#pragma once

namespace Engine::Input
{
	union Value;
}

namespace PhysicsEngineAPI::Utils::Math
{
	union Vector3;
}


namespace Engine::Math
{
	struct Vector3 : DirectX::SimpleMath::Vector3
	{
		using DirectX::SimpleMath::Vector3::Zero;
		using DirectX::SimpleMath::Vector3::One;

		Vector3(float x, float y, float z) noexcept;
		Vector3(DirectX::SimpleMath::Vector3 vector) noexcept;
		Vector3(const Input::Value& value) noexcept;
		Vector3(const PhysicsEngineAPI::Utils::Math::Vector3& value) noexcept;

		Vector3& operator=(const DirectX::SimpleMath::Vector3& vector) noexcept;
		Vector3& operator=(const Input::Value& value) noexcept;
		Vector3& operator=(const PhysicsEngineAPI::Utils::Math::Vector3& value) noexcept;
	};
}
