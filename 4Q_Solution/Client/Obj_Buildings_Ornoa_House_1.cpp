#include "pch.h"
#include "Obj_Buildings_Ornoa_House_1.h"

Obj_Buildings_Ornoa_House_1::Obj_Buildings_Ornoa_House_1(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
