#include "pch.h"
#include "Point.h"

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
