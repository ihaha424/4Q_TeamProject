#include "pch.h"
#include "InteractObejct.h"

InteractObejct::InteractObejct(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: _staticMesh(nullptr), _meshPath(std::forward<std::filesystem::path>(meshPath))
	, _rigidStatic{ nullptr }, _physicsPath{ std::forward<std::filesystem::path>(physicsPath) }
{
}

void InteractObejct::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>(this);
	_rigidStatic = componentFactory->Clone<Engine::Component::RigidKinematic>(this);
}

void InteractObejct::DisposeComponents()
{
	_staticMesh->Dispose();
	_rigidStatic->Dispose();
}

void InteractObejct::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_staticMesh->SetFilePath(_meshPath);
	_matrix = _transform.GetMatrix();
	_staticMesh->SetMatrix(&_matrix);

	auto PhysicsManager = modules.physicsManager;

	Engine::Physics::RigidComponentDesc desc;
	desc.rigidType = Engine::Physics::RigidBodyType::Kinematic;
	desc.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Box;
	desc.shapeDesc.geometryDesc.data = { _boxScale.x, _boxScale.y, _boxScale.z, 0 };
	desc.shapeDesc.isExclusive = true;
	desc.shapeDesc.materialDesc.data = { 0.f,0.f,0.f };

	Engine::Transform shapeTransform{};
	PhysicsManager->CreateStatic(&_rigidStatic->_rigidbody, desc, _transform, shapeTransform);
	_rigidStatic->_rigidbody->SetOwner(this);

	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene))->AddActor(_rigidStatic->_rigidbody);


	PhysicsManager->CreateStaticBoundBoxActor(&_rigidStatic->_boundBox, _boxScale, _transform);
	_rigidStatic->_boundBox->SetOwner(this);
	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::cameraScene))->AddActor(_rigidStatic->_boundBox);


	/*
		GameStateManagerSetting
	*/
	modules.gameStateManager->Subscribe;


}

void InteractObejct::SetIsPublic(bool isPublic)
{
	_isPublic = isPublic;
}

void InteractObejct::SetisDynamic(bool isDynamic)
{
	_isDynamic = isDynamic;
}

void InteractObejct::SetHasMesh(bool hasMesh)
{
	_hasMesh = hasMesh;
}

void InteractObejct::SetBoxScale(Engine::Math::Vector3 boxScale)
{
	_boxScale = boxScale;
}
