#include "pch.h"
#include "Obj_Buildings_Sudium.h"

Obj_Buildings_Sudium::Obj_Buildings_Sudium(const std::filesystem::path& meshPath,
	const std::filesystem::path& physicsPath):
	StaticObject(meshPath, physicsPath)
{
}
