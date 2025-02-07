#include "pch.h"
#include "Obj_Buildings_Hide_House_4.h"

Obj_Buildings_Hide_House_4::Obj_Buildings_Hide_House_4(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
