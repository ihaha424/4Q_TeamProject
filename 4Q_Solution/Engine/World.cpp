#include "pch.h"
#include "World.h"

void Engine::World::Initialize()
{
	std::ranges::for_each(_objects, [](Object* object) { object->Initialize(); });
}

void Engine::World::Attach()
{
	std::ranges::for_each(_objects, [](Object* object) { object->Attach(); });
}

void Engine::World::Update(float deltaTime)
{
	std::ranges::for_each(_objects, [deltaTime](Object* object) { object->Update(deltaTime); });
}

void Engine::World::FixedUpdate()
{
	std::ranges::for_each(_objects, [](Object* object) { object->FixedUpdate(); });
}

void Engine::World::Detach()
{
	std::ranges::for_each(_objects, [](Object* object) { object->Detach(); });
}

void Engine::World::Finalize()
{
	std::ranges::for_each(_objects, [](Object* object) { object->Finalize(); });
}

void Engine::World::LoadWorldFromFile(const std::filesystem::path& filePath)
{
	// TODO: Load World From File
}
