#pragma once
#include "StaticObject.h"

class Building9 : public StaticObject
{
public:
	explicit Building9(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
};

