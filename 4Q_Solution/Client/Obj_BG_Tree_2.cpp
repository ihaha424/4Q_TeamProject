#include "pch.h"
#include "Obj_BG_Tree_2.h"

Obj_BG_Tree_2::Obj_BG_Tree_2(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{
}
