#include "pch.h"
#include "BG_Props_Fence.h"

BG_Props_Fence::BG_Props_Fence(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath):
	StaticObject(meshPath, physicsPath)
{
}
