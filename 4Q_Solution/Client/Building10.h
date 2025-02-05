#pragma once
#include "StaticObject.h"

class Building10 : public StaticObject
{
public:
	explicit Building10(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
};

