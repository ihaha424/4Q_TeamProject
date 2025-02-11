#include "pch.h"
#include "Obj_Hide_Potion.h"

Obj_Hide_Potion::Obj_Hide_Potion(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath):
	StaticObject(meshPath, physicsPath)
{
}
