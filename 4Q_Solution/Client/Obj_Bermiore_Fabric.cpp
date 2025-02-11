#include "pch.h"
#include "Obj_Bermiore_Fabric.h"

Obj_Bermiore_Fabric::Obj_Bermiore_Fabric(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath) :
	StaticObject(meshPath, physicsPath)
{
}
