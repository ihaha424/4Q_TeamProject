#include "pch.h"
#include "Terrain.h"


Terrain::Terrain(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath) :
	_staticMesh(nullptr), _meshPath(std::forward<std::filesystem::path>(meshPath)),
	_rigidStatc{ nullptr }, _physicsPath{ std::forward<std::filesystem::path>(physicsPath) }
{
}

void Terrain::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>(this);
	_rigidStatc = componentFactory->Clone<Engine::Component::RigidStatic>(this);
}

void Terrain::DisposeComponents()
{
	_staticMesh->Dispose();
	_rigidStatc->Dispose();
}

void Terrain::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_staticMesh->SetFilePath(_meshPath);
	_staticMesh->SetMatrix(&_matrix);

	auto PhysicsManager = Engine::Application::GetPhysicsManager();
	Engine::Physics::GeometryDesc geometryDesc;
	geometryDesc.data = { 1, 1, 1 };
	PhysicsManager->LoadTriangleMesh(geometryDesc, "terrain", "../Resources/Level/Level.fbx");
	Engine::Transform transform{};
	PhysicsManager->CreateTriangleStatic(&_rigidStatc->_rigidbody, "terrain", { {0.f,0.f,0.f } }, transform);
	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::cameraScene))->AddActor(_rigidStatc->_rigidbody);

	PhysicsManager->CreateStaticBoundBoxActor(&_rigidStatc->_boundBox);
	PhysicsManager->GetScene(1)->AddActor(_rigidStatc->_boundBox);
}

void Terrain::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	_matrix = Engine::Math::Matrix::CreateTranslation(0.f, 0.f, 100.f);
}
