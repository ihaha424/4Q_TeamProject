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
	_tempMesh = componentFactory->Clone<Engine::Component::RigidStatic>();
}

void Terrain::DisposeComponents()
{
	_staticMesh->Dispose();
	_terrainMesh->Dispose();
	_tempMesh->Dispose();
}

void Terrain::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_staticMesh->SetFilePath(_meshPath);
	_staticMesh->SetMatrix(&_matrix);

	auto PhysicsManager = Engine::Application::GetPhysicsManager();

	{
		Engine::Physics::GeometryDesc geometryDesc;
		geometryDesc.data = { 1, 1, 1 };
		PhysicsManager->LoadTriangleMesh(geometryDesc, "terrain", "../Resources/Level/Level.fbx");
		Engine::Transform transform{};
		PhysicsManager->CreateTriangleStatic(&_terrainMesh->_rigidbody, "terrain", { {0.f,0.f,0.f } }, transform);
		PhysicsManager->GetScene(0)->AddActor(_terrainMesh->_rigidbody);
		_terrainMesh->_rigidbody->SetTranslate({ 0, -500, 0 });

		PhysicsManager->CreateStaticBoundBoxActor(&_terrainMesh->_boundBox);
		PhysicsManager->GetScene(1)->AddActor(_terrainMesh->_boundBox);
		_terrainMesh->_rigidbody->SetTranslate({ 0, -500, 0 });
	}

	{
		Engine::Physics::RigidComponentDesc desc;
		desc.rigidType = Engine::Physics::RigidBodyType::Static;						//&&
		desc.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Box;
		desc.shapeDesc.geometryDesc.data = { 100.f, 100.f, 100.f };
		desc.shapeDesc.isExclusive = true;
		desc.shapeDesc.materialDesc.data = { 0.5f,0.5f,0.f };
		// 2. Transform ¸¸µé±â
		Engine::Transform transform{};
		transform.position = { 0,-500,0 };

		PhysicsManager->CreateStatic(&_tempMesh->_rigidbody, desc, transform);
		PhysicsManager->GetScene(0)->AddActor(_tempMesh->_rigidbody);

		PhysicsManager->CreateStaticBoundBoxActor(&_tempMesh->_boundBox);
		PhysicsManager->GetScene(1)->AddActor(_tempMesh->_boundBox);
	}

}

void Terrain::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
	_matrix = Engine::Math::Matrix::CreateTranslation(0.f, 0.f, 100.f);
}
