#pragma once
#include "StaticObject.h"

class Building8 : public StaticObject
{
public:
	explicit Building8(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
};

