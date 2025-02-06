#include "pch.h"
#include "Obj_Buildings_Bermiore_Atelier_3.h"

Obj_Buildings_Bermiore_Atelier_3::Obj_Buildings_Bermiore_Atelier_3(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
