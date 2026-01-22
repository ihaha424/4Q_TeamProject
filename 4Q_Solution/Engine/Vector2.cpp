#include "pch.h"
#include "Vector2.h"

Engine::Math::Vector2::Vector2(const float x, const float y) noexcept :
	DirectX::SimpleMath::Vector2(x, y)
{
}

Engine::Math::Vector2::Vector2(const DirectX::SimpleMath::Vector2& vector) noexcept
	: DirectX::SimpleMath::Vector2(vector)
{
}

Engine::Math::Vector2& Engine::Math::Vector2::operator=(const DirectX::SimpleMath::Vector2& vector) noexcept
{
	DirectX::SimpleMath::Vector2::operator=(vector);
	return *this;
}
