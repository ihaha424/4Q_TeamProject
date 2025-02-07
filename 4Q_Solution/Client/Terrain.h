#pragma once
#include "StaticObject.h"

class Terrain : public StaticObject
{
public:
	explicit Terrain(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);

protected:
	void PreInitialize(const Engine::Modules& modules) override;
};

