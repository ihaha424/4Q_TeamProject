#pragma once

namespace Engine::Math
{
	struct Rect : DirectX::SimpleMath::Rectangle
	{
		Rect() = default;
		Rect(long x, long y, long width, long height) noexcept;
		Rect(Point point, Size size) noexcept;
	};
}