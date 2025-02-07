#include "pch.h"
#include "Obj_Props_Fence.h"

Obj_Props_Fence::Obj_Props_Fence(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
