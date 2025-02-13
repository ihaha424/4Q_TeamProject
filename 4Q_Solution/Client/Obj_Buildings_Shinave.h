#pragma once
#include "StaticObject.h"

class Obj_Buildings_Shinave : public StaticObject
{
public:
	explicit Obj_Buildings_Shinave(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Obj_Buildings_Shinave() = default;
};

