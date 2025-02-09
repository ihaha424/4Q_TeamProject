#include "pch.h"
#include "GrabbedObject.h"

GrabbedObject::GrabbedObject(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath)
	: _staticMesh(nullptr), _meshPath(std::forward<std::filesystem::path>(meshPath))
	, _rigidKinematic{ nullptr }, _physicsPath{ std::forward<std::filesystem::path>(physicsPath) }
	, _catchOnwerTransform{ nullptr }, _maxRotation{ std::numbers::pi_v<float> / 4 }
	, _minDistance{ 20.f }, _maxDistance{ 1000.f }, _moveSpeed{ 0.1f }
{
}

void GrabbedObject::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>(this);
	_rigidKinematic = componentFactory->Clone<Engine::Component::RigidKinematic>(this);
}

void GrabbedObject::SetIsPublic(bool isPublic)
{
	_isPublic = isPublic;
}

void GrabbedObject::SetisDynamic(bool isDynamic)
{
	_isDynamic = isDynamic;
}

void GrabbedObject::SetHasMesh(bool hasMesh)
{
	_hasMesh = hasMesh;
}

void GrabbedObject::SetBoxScale(Engine::Math::Vector3 boxScale)
{
	_boxScale = boxScale;
}

bool GrabbedObject::Grabbed(Engine::Transform* ownerTransform)
{
	auto direction = _transform.position - ownerTransform->position;
	if (direction.Length() < _minDistance || direction.Length() > _maxDistance)
		return false;
	_catchOnwerTransform = ownerTransform;
	_prevOnwerTransform = *ownerTransform;
	//TODO: 서버에세 잡았어 메세지


	return true;
}

void GrabbedObject::PutThis()
{
	_catchOnwerTransform = nullptr;
	//TODO 서버에게 놓았어 메세지
}

void GrabbedObject::PreUpdate(float deltaTime)
{
	if (nullptr == _catchOnwerTransform)
		return;
	auto direction = _transform.position - _catchOnwerTransform->position;
	float angle = direction.Dot(_catchOnwerTransform->GetForward());
	if (direction.Length() < _minDistance || direction.Length() > _maxDistance || angle > _maxRotation)
	{
		_catchOnwerTransform = nullptr;
		return;
		//TODO 서버에게 놓았어 메세지
	}
	_prevOnwerTransform.rotation.Conjugate();
	Engine::Math::Quaternion deltaRot = _catchOnwerTransform->rotation * _prevOnwerTransform.rotation;
	direction = Engine::Math::Vector3::Transform(direction, deltaRot);
	auto translate = _catchOnwerTransform->position - _prevOnwerTransform.position;

	_transform.position = _catchOnwerTransform->position + direction + translate;
	_prevOnwerTransform = *_catchOnwerTransform;
	//TODO 서버에게 이 오브젝트의_transform 보내기(worldPos값)
	std::cout << "x: " << _transform.position.x << " y: " << _transform.position.y << " z: " << _transform.position.z << std::endl;
}

void GrabbedObject::PostUpdate(float deltaTime)
{
	Object::PostUpdate(deltaTime);

	_rigidKinematic->_boundBox->SetTransform(_transform);
	_rigidKinematic->_rigidbody->SetTransform(_transform);
	_matrix = _transform.GetMatrix();
}

void GrabbedObject::DisposeComponents()
{
	_staticMesh->Dispose();
	_rigidKinematic->Dispose();
}

void GrabbedObject::PreInitialize(const Engine::Modules& modules)
{
	Object::PreInitialize(modules);
	_staticMesh->SetFilePath(_meshPath);
	_matrix = _transform.GetMatrix();
	_staticMesh->SetMatrix(&_matrix);

	auto PhysicsManager = Engine::Application::GetPhysicsManager();

	Engine::Physics::RigidComponentDesc desc;
	desc.rigidType = Engine::Physics::RigidBodyType::Kinematic;
	desc.shapeDesc.geometryDesc.type = Engine::Physics::GeometryShape::Box;
	desc.shapeDesc.geometryDesc.data = { _boxScale.x, _boxScale.y, _boxScale.z, 0 };
	desc.shapeDesc.isExclusive = true;
	desc.shapeDesc.materialDesc.data = { 0.f,0.f,0.f };

	Engine::Transform shapeTransform{};
	PhysicsManager->CreateKinematic(&_rigidKinematic->_rigidbody, desc, _transform, 1, shapeTransform);
	_rigidKinematic->_rigidbody->SetOwner(this);

	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::mainScene))->AddActor(_rigidKinematic->_rigidbody);


	PhysicsManager->CreateStaticBoundBoxActor(&_rigidKinematic->_boundBox, _boxScale, _transform);
	_rigidKinematic->_boundBox->SetOwner(this);
	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::cameraScene))->AddActor(_rigidKinematic->_boundBox);
}
