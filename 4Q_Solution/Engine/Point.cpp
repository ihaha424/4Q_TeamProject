#include "pch.h"
#include "Point.h"

const Engine::Math::Point Engine::Math::Point::Zero = Point(0, 0);

Engine::Math::Point::Point(const long x, const long y) :
	POINT(x, y)
{
}

Engine::Math::Point::Point(const POINT& point) noexcept :
	POINT(point)
{
}

Engine::Math::Point& Engine::Math::Point::operator=(const POINT& point) noexcept
{
	POINT::operator=(point);
	return *this;
}
