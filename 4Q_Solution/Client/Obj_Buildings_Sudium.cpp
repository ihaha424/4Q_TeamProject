#include "pch.h"
#include "Obj_Buildings_Sudium.h"

Obj_Buildings_Sudium::Obj_Buildings_Sudium(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
