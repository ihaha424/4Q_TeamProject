#include "pch.h"
#include "Obj_Buildings_Shinave.h"

Obj_Buildings_Shinave::Obj_Buildings_Shinave(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
