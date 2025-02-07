#pragma once
#include "StaticObject.h"

class Obj_BG_Tree_1 : public StaticObject
{
public:
	explicit Obj_BG_Tree_1(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
};

