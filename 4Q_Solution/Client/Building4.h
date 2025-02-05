#pragma once
#include "StaticObject.h"

class Building4 : public StaticObject
{
public:
	explicit Building4(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
};

