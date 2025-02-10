#include "pch.h"
#include "Obj_Sudium_bouquet.h"

Obj_Sudium_bouquet::Obj_Sudium_bouquet(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath) :
	InteractObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath)),
	_gameStateManager(nullptr)
{
	_index = 0;
}
void Obj_Sudium_bouquet::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
}

void Obj_Sudium_bouquet::Interact()
{
}

void Obj_Sudium_bouquet::DisposeComponents()
{
	InteractObject::DisposeComponents();
}

void Obj_Sudium_bouquet::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);
}
