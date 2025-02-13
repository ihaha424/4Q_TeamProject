#include "pch.h"
#include "Rect.h"

Engine::Math::Rect::Rect(const long x, const long y, const long width, const long height) noexcept :
	Rectangle(x, y, width, height)
{
}

Engine::Math::Rect::Rect(const Point point, const Size size) noexcept :
	Rectangle(point.x, point.y, size.cx, size.cy)
{
}