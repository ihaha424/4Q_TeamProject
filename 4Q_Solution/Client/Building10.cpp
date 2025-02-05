#include "pch.h"
#include "Building10.h"

Building10::Building10(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
