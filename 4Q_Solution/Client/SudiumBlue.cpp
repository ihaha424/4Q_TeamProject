#include "pch.h"
#include "SudiumBlue.h"

SudiumBlue::SudiumBlue(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
