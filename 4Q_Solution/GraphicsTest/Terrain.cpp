#include "pch.h"
#include "BG_Terrain.h"


BG_Terrain::BG_Terrain(std::filesystem::path&& meshPath) :
	_staticMesh(nullptr), _meshPath(std::forward<std::filesystem::path>(meshPath))
{
}

void BG_Terrain::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>(this);
}

void BG_Terrain::DisposeComponents()
{
	_staticMesh->Dispose();
}

void BG_Terrain::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_staticMesh->SetFilePath(_meshPath);
	_staticMesh->SetMatrix(&_matrix);
}

void BG_Terrain::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	_matrix = Engine::Math::Matrix::CreateTranslation(0.f, 0.f, 100.f);
}
