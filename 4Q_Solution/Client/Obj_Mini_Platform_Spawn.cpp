#include "pch.h"
#include "Obj_Mini_Platform_Spawn.h"

Obj_Mini_Platform_Spawn::Obj_Mini_Platform_Spawn(const std::filesystem::path& meshPath,
	const std::filesystem::path& physicsPath):
	StaticObject(meshPath, physicsPath)
{
}
