#include "pch.h"
#include "Terrain.h"


Terrain::Terrain(std::filesystem::path&& meshPath) :
	_staticMesh(nullptr), _meshPath(std::forward<std::filesystem::path>(meshPath))
{
}

void Terrain::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>();
	_terrainMesh = componentFactory->Clone<Engine::Component::RigidStatic>();
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
	PhysicsManager->LoadTriangleMesh(geometryDesc, "terrain", "../Resources/Terrain/landscapelowpoly.fbx");
	Engine::Transform transform{};
	PhysicsManager->CreateStatic(&_terrainMesh->_rigidbody, "terrain", { {0.f,0.f,0.f } }, transform);
	PhysicsManager->GetScene(0)->AddActor(_terrainMesh->_rigidbody);
	_terrainMesh->_rigidbody->SetTranslate({-100,-100,-100});

	PhysicsManager->CreateStaticBoundBoxActor(&_terrainMesh->_boundBox);
	PhysicsManager->GetScene(1)->AddActor(_terrainMesh->_boundBox);
	_terrainMesh->_boundBox->SetTranslate({ -100,-100,-100 });
}

void Terrain::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	_matrix = Engine::Math::Matrix::CreateTranslation(0.f, 0.f, 100.f);
}
