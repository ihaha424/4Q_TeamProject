#pragma once
#include "StaticObject.h"

class Obj_Buildings_Sudium : public StaticObject
{
public:
	explicit Obj_Buildings_Sudium(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~Obj_Buildings_Sudium() = default;
};

