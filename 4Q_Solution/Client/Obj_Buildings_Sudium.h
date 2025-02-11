#pragma once
#include "StaticObject.h"

class Obj_Buildings_Sudium : public StaticObject
{
public:
	Obj_Buildings_Sudium(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
};

