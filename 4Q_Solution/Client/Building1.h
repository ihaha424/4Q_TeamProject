#pragma once
#include "StaticObject.h"

class Building1 : public StaticObject
{
public:
	explicit Building1(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
};

