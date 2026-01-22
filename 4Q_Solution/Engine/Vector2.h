#pragma once

namespace Engine::Math
{
	struct Vector2 : DirectX::SimpleMath::Vector2
	{
		using DirectX::SimpleMath::Vector2::Zero;
		using DirectX::SimpleMath::Vector2::One;

		Vector2() noexcept = default;
		Vector2(float x, float y) noexcept;

		Vector2(const DirectX::SimpleMath::Vector2& vector) noexcept;

		Vector2& operator=(const DirectX::SimpleMath::Vector2& vector) noexcept;
	};
}
