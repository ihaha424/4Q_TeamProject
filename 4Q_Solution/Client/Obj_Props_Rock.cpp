#include "pch.h"
#include "Obj_Props_Rock.h"

Obj_Props_Rock::Obj_Props_Rock(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: StaticObject(meshPath, physicsPath)
{
}
