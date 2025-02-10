#include "pch.h"
#include "BaseWoolball.h"

BaseWoolball::BaseWoolball(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath) :
	InteractObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath)),
	_gameStateManager(nullptr)
{
}

void BaseWoolball::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	InteractObject::Prepare(componentFactory);
}

void BaseWoolball::DisposeComponents()
{
	InteractObject::DisposeComponents();
}

void BaseWoolball::PreInitialize(const Engine::Modules& modules)
{
	InteractObject::PreInitialize(modules);

	_gameStateManager = modules.gameStateManager->FindSubManager(L"puzzle_01");


}
