#include "pch.h"
#include "Obj_Props_Bermiore_Cloth_2.h"

Obj_Props_Bermiore_Cloth_2::Obj_Props_Bermiore_Cloth_2(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
