#include "pch.h"
#include "ImageWrapper.h"

Engine::UI::Wrapper::Image::Image(Math::Rect* rect, const std::filesystem::path& path) :
	Wrapper(rect), _path(path)
{
}
