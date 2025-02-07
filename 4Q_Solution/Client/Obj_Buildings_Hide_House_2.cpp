#include "pch.h"
#include "Obj_Buildings_Hide_House_2.h"

Obj_Buildings_Hide_House_2::Obj_Buildings_Hide_House_2(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
