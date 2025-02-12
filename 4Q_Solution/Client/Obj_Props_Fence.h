#pragma once
#include "StaticObject.h"

class Obj_Props_Fence : public StaticObject
{
public:
	explicit Obj_Props_Fence(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Obj_Props_Fence() = default;
};

