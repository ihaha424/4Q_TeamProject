#include "pch.h"
#include "Size.h"

const Engine::Math::Size Engine::Math::Size::Zero{ 0, 0 };

Engine::Math::Size::Size(const long cx, const long cy) noexcept :
	SIZE{ cx, cy }
{
}

Engine::Math::Size::Size(const SIZE& size) noexcept :
	SIZE(size)
{
}

Engine::Math::Size& Engine::Math::Size::operator=(const SIZE& size) noexcept
{
	SIZE::operator=(size);
	return *this;
}
