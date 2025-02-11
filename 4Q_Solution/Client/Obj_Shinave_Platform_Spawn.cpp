#include "pch.h"
#include "Obj_Shinave_Platform_Spawn.h"

Obj_Shinave_Platform_Spawn::Obj_Shinave_Platform_Spawn(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: StaticObject(meshPath, physicsPath)
{
}

void Obj_Shinave_Platform_Spawn::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	StaticObject::Prepare(componentFactory);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
}

void Obj_Shinave_Platform_Spawn::SetActive(const PlayMsg::ObjectActive* msg)
{
	_staticMesh->SetActiveDraw(true);
}

void Obj_Shinave_Platform_Spawn::DisposeComponents()
{
	StaticObject::DisposeComponents();
	_sync->Dispose();
}

void Obj_Shinave_Platform_Spawn::PreInitialize(const Engine::Modules& modules)
{
	StaticObject::PreInitialize(modules);
	_staticMesh->SetActiveDraw(false);
	_sync->AddCallback((short)PacketID::ObjectActive, &Obj_Shinave_Platform_Spawn::SetActive, this);
}
