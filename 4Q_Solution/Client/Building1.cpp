#include "pch.h"
#include "Building1.h"

Building1::Building1(std::filesystem::path&& meshPath)
	: _staticMesh(nullptr), _meshPath(std::forward<std::filesystem::path>(meshPath))
{
}

void Building1::Prepare(Engine::Content::Factory::Component* componentFactory)
{
}

void Building1::DisposeComponents()
{
}

void Building1::PreInitialize(const Engine::Modules& modules)
{
}

void Building1::PostInitialize(const Engine::Modules& modules)
{
}
