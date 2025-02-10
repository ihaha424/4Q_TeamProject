#pragma once
#include "StaticObject.h"

class Obj_Props_Fence : public StaticObject
{
public:
	explicit Obj_Props_Fence(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~Obj_Props_Fence() = default;
};

