#include "pch.h"
#include "Obj_BG_Mountain.h"

Obj_BG_Mountain::Obj_BG_Mountain(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: StaticObject((meshPath), (physicsPath))
{
}
