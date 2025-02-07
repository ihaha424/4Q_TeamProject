#include "pch.h"
#include "Obj_Props_Bermiore_Cloth_1.h"

Obj_Props_Bermiore_Cloth_1::Obj_Props_Bermiore_Cloth_1(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
