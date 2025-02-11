#include "pch.h"
#include "BG_Terrain.h"


BG_Terrain::BG_Terrain(std::filesystem::path&& meshPath) :
	_staticMesh(nullptr), _meshPath(std::forward<std::filesystem::path>(meshPath))
{
}

void BG_Terrain::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>(this);
	_terrainMesh = componentFactory->Clone<Engine::Component::RigidStatic>(this);
}

void BG_Terrain::DisposeComponents()
{
	_staticMesh->Dispose();
	_terrainMesh->Dispose();
}

void BG_Terrain::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_staticMesh->SetFilePath(_meshPath);
	_staticMesh->SetMatrix(&_matrix);

	auto PhysicsManager = Engine::Application::GetPhysicsManager();
	Engine::Physics::GeometryDesc geometryDesc;
	geometryDesc.data = {1, 1, 1};
	PhysicsManager->LoadTriangleMesh(geometryDesc, "terrain", "../Resources/Level/Level.fbx");
	Engine::Transform transform{};
	PhysicsManager->CreateTriangleStatic(&_terrainMesh->_rigidbody, "terrain", { {0.f,0.f,0.f } }, transform);
	PhysicsManager->GetScene(0)->AddActor(_terrainMesh->_rigidbody);
	//_terrainMesh->_rigidbody->SetTranslate({ -1000.f, -200.f, 1000.f });

	PhysicsManager->CreateStaticBoundBoxActor(&_terrainMesh->_boundBox);
	PhysicsManager->GetScene(1)->AddActor(_terrainMesh->_boundBox);
	//_terrainMesh->_boundBox->SetTranslate({ -1000.f, -200.f, 1000.f });
}

void BG_Terrain::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	_matrix = Engine::Math::Matrix::CreateTranslation(-1000.f, -200.f, 1000.f);
}
