#include "pch.h"
#include "Obj_Hide_Box.h"

Obj_Hide_Box::Obj_Hide_Box(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath):
	StaticObject(meshPath, physicsPath)
{
}
