#include "pch.h"
#include "Terrain.h"


Terrain::Terrain(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: StaticObject(std::forward<std::filesystem::path>(meshPath), std::forward<std::filesystem::path>(physicsPath))
{}

void Terrain::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_staticMesh->SetFilePath(_meshPath);
	_matrix = _transform.GetMatrix();
	_staticMesh->SetMatrix(&_matrix);



	auto PhysicsManager = Engine::Application::GetPhysicsManager();

	Engine::Physics::GeometryDesc geometryDesc;
	geometryDesc.data = { _transform.scale.x, _transform.scale.y, 1 };
	PhysicsManager->LoadHeightMap(geometryDesc, "terrain", "../Resources/Terrain/HeightMap.png");

	Engine::Transform transform{};
	PhysicsManager->CreateTriangleStatic(&_rigidStatc->_rigidbody, "terrain", { {0.2f,0.f,0.f } }, transform);
	_rigidStatc->_rigidbody->SetOwner(this);
	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene))->AddActor(_rigidStatc->_rigidbody);

	//TODO: Scale을 어떻게 조절 할지???
	PhysicsManager->CreateStaticBoundBoxActor(&_rigidStatc->_boundBox, _transform.scale, _transform);
	_rigidStatc->_boundBox->SetOwner(this);
	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::cameraScene))->AddActor(_rigidStatc->_boundBox);


}
