#include "pch.h"
#include "Obj_Shinave_SteppedSudium.h"

Obj_Shinave_SteppedSudium::Obj_Shinave_SteppedSudium(const std::filesystem::path& meshPath,
	const std::filesystem::path& physicsPath) :
	StaticObject(meshPath, physicsPath)
{
}
