#pragma once
#include "StaticObject.h"

class BG_Terrain : public StaticObject
{
public:
	explicit BG_Terrain(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);

protected:
	void PreInitialize(const Engine::Modules& modules) override;

	void PreUpdate(float deltaTime) override;
};
