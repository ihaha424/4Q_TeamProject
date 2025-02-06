#include "pch.h"
#include "Obj_Buildings_Ornoa_House_3.h"

Obj_Buildings_Ornoa_House_3::Obj_Buildings_Ornoa_House_3(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
