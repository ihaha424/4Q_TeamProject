#include "pch.h"
#include "Obj_Shinave_Platform_Set.h"


Obj_Shinave_Platform_Set::Obj_Shinave_Platform_Set(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: StaticObject(meshPath, physicsPath)
{
}
