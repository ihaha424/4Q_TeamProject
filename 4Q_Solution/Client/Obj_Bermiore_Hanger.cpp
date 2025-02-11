#include "pch.h"
#include "Obj_Bermiore_Hanger.h"

Obj_Bermiore_Hanger::Obj_Bermiore_Hanger(const std::filesystem::path& meshPath,
	const std::filesystem::path& physicsPath) :
	StaticObject(meshPath, physicsPath)
{
}
