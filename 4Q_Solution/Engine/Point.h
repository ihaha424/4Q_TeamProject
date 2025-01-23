#pragma once

namespace Engine::Math
{
	struct Point : POINT
	{
		Point() noexcept = default;
		Point(long x, long y);

		Point(const POINT& point) noexcept;

		Point& operator=(const POINT& point) noexcept;
	};
}
