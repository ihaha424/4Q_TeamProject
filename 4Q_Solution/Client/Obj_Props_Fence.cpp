#include "pch.h"
#include "Obj_Props_Fence.h"

Obj_Props_Fence::Obj_Props_Fence(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: StaticObject((meshPath), (physicsPath))
{
}
