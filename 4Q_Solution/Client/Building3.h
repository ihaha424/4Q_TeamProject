#pragma once
#include "StaticObject.h"

class Building3 : public StaticObject
{
public:
	explicit Building3(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
};

