#include "pch.h"
#include "Terrain.h"


Terrain::Terrain(std::filesystem::path&& meshPath) :
	_staticMesh(nullptr), _meshPath(std::forward<std::filesystem::path>(meshPath))
{
}

void Terrain::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>();
	_terrainMesh = componentFactory->Clone<Engine::Component::Rigid>();
}

void Terrain::DisposeComponents()
{
	_staticMesh->Dispose();
	_terrainMesh->Dispose();
}

void Terrain::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_staticMesh->SetFilePath(_meshPath);
	_staticMesh->SetMatrix(&_matrix);

	auto PhysicsManager = Engine::Application::GetPhysicsManager();
	Engine::Physics::GeometryDesc geometryDesc;
	geometryDesc.data = {1, 1, 1};
	PhysicsManager->LoadTriangleMesh(geometryDesc, "terrain", "../path");
	/*PhysicsManager->CreateStatic();*/
}

void Terrain::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	_matrix = Engine::Math::Matrix::CreateTranslation(0.f, 0.f, 100.f);
}
