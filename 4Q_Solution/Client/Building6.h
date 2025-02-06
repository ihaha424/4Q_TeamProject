#pragma once
#include "StaticObject.h"

class Building6 : public StaticObject
{
public:
	explicit Building6(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
};

