#pragma once
#include "StaticObject.h"

class Obj_Buildings_Shinave : public StaticObject
{
public:
	explicit Obj_Buildings_Shinave(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
};

