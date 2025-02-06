#pragma once
#include "StaticObject.h"

class Building2 : public StaticObject
{
public:
	explicit Building2(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
};

