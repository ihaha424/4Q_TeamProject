#include "pch.h"
#include "Obj_BG_Tree_1.h"

Obj_BG_Tree_1::Obj_BG_Tree_1(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
