#pragma once
#include "StaticObject.h"

class Building7 : public StaticObject
{
public:
	explicit Building7(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
};

