#include "pch.h"
#include "Obj_Hide_Plant.h"

Obj_Hide_Plant::Obj_Hide_Plant(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: StaticObject(meshPath, physicsPath)
{
}


void Obj_Hide_Plant::PreInitialize(const Engine::Modules& modules)
{
	StaticObject::PreInitialize(modules);
}

void Obj_Hide_Plant::PostInitialize(const Engine::Modules& modules)
{
	StaticObject::PostInitialize(modules);
	_staticMesh->SetActiveDraw(false);
}
