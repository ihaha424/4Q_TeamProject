#include "pch.h"
#include "StaticObject.h"

StaticObject::StaticObject(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: _staticMesh(nullptr), _meshPath(std::forward<std::filesystem::path>(meshPath))
	, _rigidStatc{ nullptr }, _physicsPath{ std::forward<std::filesystem::path>(physicsPath) }
{
}

void StaticObject::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>(this);
	_rigidStatc = componentFactory->Clone<Engine::Component::RigidStatic>(this);
}

void StaticObject::DisposeComponents()
{
	_staticMesh->Dispose();
	_rigidStatc->Dispose();
}

void StaticObject::SetIsPublic(bool isPublic)
{
	_isPublic = isPublic;
}

void StaticObject::SetisDynamic(bool isDynamic)
{
	_isDynamic = isDynamic;
}

void StaticObject::SetHasMesh(bool hasMesh)
{
	_hasMesh = hasMesh;
}

void StaticObject::SetBoxScale(Engine::Math::Vector3 boxScale)
{
	_boxScale = boxScale;
}

void StaticObject::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_staticMesh->SetFilePath(_meshPath);
	_matrix = _transform.GetMatrix();
	_staticMesh->SetMatrix(&_matrix);
	
	auto PhysicsManager = Engine::Application::GetPhysicsManager();
	if (_hasMesh)
	{
		Engine::Physics::GeometryDesc geometryDesc;
		Engine::Transform shapeTransform{};
		geometryDesc.data = { _transform.scale.x, _transform.scale.y, _transform.scale.z, 0 };
		PhysicsManager->LoadTriangleMesh(geometryDesc, _physicsPath.string().c_str(), _physicsPath.string().c_str());
		PhysicsManager->CreateTriangleStatic(&_rigidStatc->_rigidbody, _physicsPath.string().c_str(), { {0.f,0.f,0.f } }, _transform, shapeTransform, false);
		_rigidStatc->_rigidbody->SetOwner(this);
	}
	else
	{
		Engine::Physics::RigidComponentDesc desc;
		desc.rigidType = Engine::Physics::RigidBodyType::Static;
		desc.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Box;
		desc.shapeDesc.geometryDesc.data = { _boxScale.x, _boxScale.y, _boxScale.z, 0 };
		desc.shapeDesc.isExclusive = true;
		desc.shapeDesc.materialDesc.data = { 0.5f,0.5f,0.f };

		Engine::Transform shapeTransform{};
		PhysicsManager->CreateStatic(&_rigidStatc->_rigidbody, desc, _transform, shapeTransform);
		_rigidStatc->_rigidbody->SetOwner(this);
	}
	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene))->AddActor(_rigidStatc->_rigidbody);


	PhysicsManager->CreateStaticBoundBoxActor(&_rigidStatc->_boundBox, _boxScale, _transform);
	_rigidStatc->_boundBox->SetOwner(this);
	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::cameraScene))->AddActor(_rigidStatc->_boundBox);
}
