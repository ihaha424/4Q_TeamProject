#pragma once
#include "StaticObject.h"

class Obj_Buildings_Ornoa_House_3 : public StaticObject
{
public:
	explicit Obj_Buildings_Ornoa_House_3(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Obj_Buildings_Ornoa_House_3() = default;
};

