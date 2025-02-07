#include "pch.h"
#include "Obj_BG_Mountain.h"

Obj_BG_Mountain::Obj_BG_Mountain(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
