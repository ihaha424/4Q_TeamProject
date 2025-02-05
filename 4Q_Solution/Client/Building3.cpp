#include "pch.h"
#include "Building3.h"

Building3::Building3(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
