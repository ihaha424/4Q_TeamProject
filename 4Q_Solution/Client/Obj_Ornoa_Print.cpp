#include "pch.h"
#include "Obj_Ornoa_Print.h"

Obj_Ornoa_Print::Obj_Ornoa_Print(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath) :
	StaticObject(meshPath, physicsPath)
{
}
