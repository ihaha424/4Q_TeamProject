#pragma once
#include "StaticObject.h"

class Building5 : public StaticObject
{
public:
	explicit Building5(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
};

