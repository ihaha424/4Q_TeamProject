#pragma once
#include "StaticObject.h"

class Obj_BG_Mountain : public StaticObject
{
public:
	explicit Obj_BG_Mountain(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
};

