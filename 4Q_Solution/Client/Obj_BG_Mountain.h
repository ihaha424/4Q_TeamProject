#pragma once
#include "StaticObject.h"

class Obj_BG_Mountain : public StaticObject
{
public:
	explicit Obj_BG_Mountain(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Obj_BG_Mountain() = default;
};

