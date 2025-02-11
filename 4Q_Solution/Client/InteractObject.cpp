#include "pch.h"
#include "InteractObject.h"

InteractObject::InteractObject(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: _staticMesh(nullptr), _meshPath(meshPath)
	, _rigidStatic{ nullptr }, _physicsPath{ physicsPath }
{
}

void InteractObject::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>(this);
	_rigidStatic = componentFactory->Clone<Engine::Component::RigidStatic>(this);
}

void InteractObject::DisposeComponents()
{
	Engine::Object::Dispose();
	_staticMesh->Dispose();
	_rigidStatic->Dispose();
}

void InteractObject::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_staticMesh->SetFilePath(_meshPath);
	_matrix = _transform.GetMatrix();
	_staticMesh->SetMatrix(&_matrix);

	auto PhysicsManager = modules.physicsManager;

	if (!_isSphere)
	{
		Engine::Physics::RigidComponentDesc desc;
		desc.rigidType = Engine::Physics::RigidBodyType::Static;
		desc.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Box;
		desc.shapeDesc.geometryDesc.data = { _boxScale.x, _boxScale.y, _boxScale.z, 0.f };
		desc.shapeDesc.isExclusive = true;
		desc.shapeDesc.materialDesc.data = { 0.5f,0.5f,0.f };

		Engine::Transform shapeTransform{};
		shapeTransform.position = _boxPosition;
		PhysicsManager->CreateStatic(&_rigidStatic->_rigidbody, desc, _transform, shapeTransform);
		_rigidStatic->_rigidbody->SetOwner(this);
	}
	else
	{
		Engine::Physics::RigidComponentDesc desc;
		desc.rigidType = Engine::Physics::RigidBodyType::Static;
		desc.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Sphere;
		desc.shapeDesc.geometryDesc.data = { _boxScale.x, 0.f, 0.f, 0.f };
		desc.shapeDesc.isExclusive = true;
		desc.shapeDesc.materialDesc.data = { 0.5f,0.5f,0.f };

		Engine::Transform shapeTransform{};
		shapeTransform.position = _boxPosition;
		PhysicsManager->CreateStatic(&_rigidStatic->_rigidbody, desc, _transform, shapeTransform);
		_rigidStatic->_rigidbody->SetOwner(this);
	}
	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene))->AddActor(_rigidStatic->_rigidbody);
}

void InteractObject::SetIsPublic(bool isPublic)
{
	_isPublic = isPublic;
}

void InteractObject::SetisDynamic(bool isDynamic)
{
	_isDynamic = isDynamic;
}

void InteractObject::SetHasMesh(bool hasMesh)
{
	_hasMesh = hasMesh;
}

void InteractObject::SetBoxScale(Engine::Math::Vector3 boxScale)
{
	_boxScale = boxScale;
}

void InteractObject::SetBoxPosition(Engine::Math::Vector3 boxPosition)
{
	_boxPosition = boxPosition;
}

void InteractObject::SetIsSphere(bool isSphere)
{
	_isSphere = isSphere;
}
