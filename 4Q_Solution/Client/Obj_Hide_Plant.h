#pragma once
#include "StaticOBject.h"

class Obj_Hide_Plant : public StaticObject
{
	public:
		explicit Obj_Hide_Plant(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
		virtual ~Obj_Hide_Plant() = default;

		void PreInitialize(const Engine::Modules & modules) override;
		void PostInitialize(const Engine::Modules& modules) override;
};

