#include "pch.h"
#include "Obj_Hide_Box.h"


int Obj_Hide_Box::_serialNumber = 15202;
Obj_Hide_Box::Obj_Hide_Box(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath):
	GrabbedObject(meshPath, physicsPath)
{
}

void Obj_Hide_Box::PreInitialize(const Engine::Modules& modules)
{
	GrabbedObject::PreInitialize(modules);
	_sync->SetSerialNumber(_serialNumber++);
}
