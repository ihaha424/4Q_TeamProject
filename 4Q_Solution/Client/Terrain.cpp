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

void Terrain::SetBoxScale(Engine::Math::Vector3 boxScale)
{
	_boxScale = boxScale;
}

void Terrain::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_staticMesh->SetFilePath(_meshPath);
	_staticMesh->SetMatrix(&_matrix);



	auto PhysicsManager = Engine::Application::GetPhysicsManager();

	Engine::Physics::GeometryDesc geometryDesc;
	geometryDesc.data = { _boxScale.x, _boxScale.y, _boxScale.z };
	PhysicsManager->LoadHeightMap(geometryDesc, "terrain", _physicsPath.string().c_str());

	Engine::Transform transform{};
	PhysicsManager->CreateTriangleStatic(&_rigidStatc->_rigidbody, "terrain", { {0.f,0.f,0.f } }, transform);
	_rigidStatc->_rigidbody->SetOwner(this);
	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene))->AddActor(_rigidStatc->_rigidbody);

	//TODO: Scale을 어떻게 조절 할지???
	PhysicsManager->CreateStaticBoundBoxActor(&_rigidStatc->_boundBox, _boxScale, _transform);
	_rigidStatc->_boundBox->SetOwner(this);
	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::cameraScene))->AddActor(_rigidStatc->_boundBox);
}

void Terrain::PostInitialize(const Engine::Modules& modules)
{
	Object::PostInitialize(modules);
}
