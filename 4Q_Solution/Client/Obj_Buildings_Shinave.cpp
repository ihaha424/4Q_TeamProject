#include "pch.h"
#include "Obj_Buildings_Shinave.h"

Obj_Buildings_Shinave::Obj_Buildings_Shinave(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: StaticObject((meshPath), (physicsPath))
{
}
