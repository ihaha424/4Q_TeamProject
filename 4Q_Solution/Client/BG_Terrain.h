#pragma once
#include "StaticObject.h"

class BG_Terrain : public StaticObject
{
public:
	BG_Terrain(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);

protected:
	void PreInitialize(const Engine::Modules& modules) override;

	void PreUpdate(float deltaTime) override;
};
