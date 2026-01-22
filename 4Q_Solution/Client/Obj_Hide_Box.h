#pragma once
#include "GrabbedObject.h"

class Obj_Hide_Box : public GrabbedObject
{
public:
	Obj_Hide_Box(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);


protected:
	void PreInitialize(const Engine::Modules& modules) override;

	static int _serialNumber;
};

