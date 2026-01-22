#pragma once
#include "StaticObject.h"

class Obj_Shinave_Platform_Set
	: public StaticObject
{
public:
	Obj_Shinave_Platform_Set(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Obj_Shinave_Platform_Set() = default;
};

