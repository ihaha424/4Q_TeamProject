#pragma once
#include "StaticObject.h"

class SudiumBlue : public StaticObject
{
public:
	explicit SudiumBlue(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
};

