#include "pch.h"
#include "World.h"

void Engine::World::Initialize()
{
	PreInitialize();
	std::ranges::for_each(_objects, [](Object* object) { object->Initialize(); });
	PostInitialize();
}

void Engine::World::Attach()
{
	PreAttach();
	std::ranges::for_each(_objects, [](Object* object) { object->Attach(); });
	PostAttach();
}

void Engine::World::Update(float deltaTime)
{
	PreUpdate(deltaTime);
	std::ranges::for_each(_objects, [deltaTime](Object* object) { object->Update(deltaTime); });
	PostUpdate(deltaTime);
}

void Engine::World::FixedUpdate()
{
	PreFixedUpdate();
	std::ranges::for_each(_objects, [](Object* object) { object->FixedUpdate(); });
	PostFixedUpdate();
}

void Engine::World::Detach()
{
	PreDetach();
	std::ranges::for_each(_objects, [](Object* object) { object->Detach(); });
	PostDetach();
}

void Engine::World::Finalize()
{
	PreFinalize();
	std::ranges::for_each(_objects, [](Object* object) { object->Finalize(); });
	PostFinalize();
}

void Engine::World::PreInitialize()
{
}

void Engine::World::PostInitialize()
{
}

void Engine::World::PreAttach()
{
}

void Engine::World::PostAttach()
{
}

void Engine::World::PreUpdate(float deltaTime)
{
}

void Engine::World::PostUpdate(float deltaTime)
{
}

void Engine::World::PreFixedUpdate()
{
}

void Engine::World::PostFixedUpdate()
{
}

void Engine::World::PreDetach()
{
}

void Engine::World::PostDetach()
{
}

void Engine::World::PreFinalize()
{
}

void Engine::World::PostFinalize()
{
}

void Engine::World::LoadWorldFromFile(const std::filesystem::path& filePath)
{
	// TODO: Load World From File
}
