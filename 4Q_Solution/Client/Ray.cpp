#include "pch.h"
#include "Ray.h"

Ray::Ray(std::filesystem::path&& meshPath)
{
	_meshPath = std::forward<std::filesystem::path>(meshPath);
}