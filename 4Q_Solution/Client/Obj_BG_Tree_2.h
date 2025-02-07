#pragma once
#include "StaticObject.h"

class Obj_BG_Tree_2 : public StaticObject
{
public:
	explicit Obj_BG_Tree_2(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~Obj_BG_Tree_2() = default;
};

