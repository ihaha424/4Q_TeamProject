#include "pch.h"
#include "GrabbedObject.h"
#include "GrabData.h"

GrabbedObject::GrabbedObject(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath)
	: _staticMesh(nullptr), _meshPath(meshPath)
	, _rigidKinematic{ nullptr }, _physicsPath{ physicsPath }
	, _catchOnwerTransform{ nullptr }, _maxRotation{ std::numbers::pi_v<float> / 4 }
	, _minDistance{ 20.f }, _maxDistance{ 1000.f }, _moveSpeed{ 0.1f }
{
}

void GrabbedObject::Prepare(Engine::Content::Factory::Component* componentFactory)
{
	_staticMesh = componentFactory->Clone<Engine::Component::StaticMesh>(this);
	_rigidKinematic = componentFactory->Clone<Engine::Component::RigidKinematic>(this);
	_sync = componentFactory->Clone<Engine::Component::Synchronize>(this);
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

void GrabbedObject::SetBoxPosition(Engine::Math::Vector3 boxPosition)
{
	_boxPosition = boxPosition;
}

void GrabbedObject::SetIsSphere(bool isSphere)
{
}

bool GrabbedObject::Grabbed(Engine::Transform* ownerTransform, bool isRemote)
{
	auto direction = _transform.position - ownerTransform->position;
	if (direction.Length() < _minDistance || direction.Length() > _maxDistance)
		return false;
	_catchOnwerTransform = ownerTransform;
	_prevOnwerTransform = *ownerTransform;
	
	if (isRemote)
	{
		_sync->_interactObject.set_objectserialnumber(_sync->GetSerialNumber());
		_sync->_interactObject.SerializeToString(&_sync->_msgBuffer);
		Client::SavePacketData(
			_sync->_msgBuffer,
			(short)PacketID::PickObject,
			_sync->_interactObject.ByteSizeLong(),
			_sync->GetSerialNumber()
		);
	}


	return true;
}

void GrabbedObject::PutThis()
{
	_catchOnwerTransform = nullptr;
	
	_sync->_interactObject.set_objectserialnumber(_sync->GetSerialNumber());
	_sync->_interactObject.SerializeToString(&_sync->_msgBuffer);
	Client::SavePacketData(
		_sync->_msgBuffer,
		(short)PacketID::PutObject,
		_sync->_interactObject.ByteSizeLong(),
		_sync->GetSerialNumber()
	);

}

void GrabbedObject::RemoteGrabbed(const PlayMsg::PickObject* msg)
{
	auto manager = GameClient::Application::GetGameStateManager();
	auto data = manager->GetData(L"GrabData");
	if (data)
	{
		auto grabData = std::any_cast<GrabData>(*data);
	
		grabData.player = msg->targetserialnumber();
		grabData.remoteGrab = nullptr;
		manager->SetData(L"GrabData", grabData);
	}
}

void GrabbedObject::RemotePutThis(const PlayMsg::PutObject* msg)
{
	Engine::Math::Vector3 position;
	const auto& pos = msg->position();
	position.x = *(pos.begin());
	position.y = *(pos.begin() + 1);
	position.z = *(pos.begin() + 2);

	auto manager = GameClient::Application::GetGameStateManager();
	auto data = manager->GetData(L"GrabData");
	if (data)
	{
		auto grabData = std::any_cast<GrabData>(*data);
		grabData.player = msg->targetserialnumber();
		grabData.remoteGrab = nullptr;
		manager->SetData(L"GrabData", grabData);
		_catchOnwerTransform = nullptr;
	}
}

void GrabbedObject::PreUpdate(float deltaTime)
{
	if (nullptr == _catchOnwerTransform)
		return;
	auto direction = _transform.position - _catchOnwerTransform->position;
	float angle = direction.Dot(_catchOnwerTransform->GetForward());
	if (direction.Length() < _minDistance || direction.Length() > _maxDistance || angle > _maxRotation)
	{
		PutThis();
		return;
	}
	_prevOnwerTransform.rotation.Conjugate();
	Engine::Math::Quaternion deltaRot = _catchOnwerTransform->rotation * _prevOnwerTransform.rotation;
	direction = Engine::Math::Vector3::Transform(direction, deltaRot);
	auto translate = _catchOnwerTransform->position - _prevOnwerTransform.position;

	_transform.position = _catchOnwerTransform->position + direction + translate;
	_prevOnwerTransform = *_catchOnwerTransform;

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
	_sync->Dispose();
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
	_rigidKinematic->_rigidbody->SetFlag(Engine::Physics::CollisionType::Collision, false);
	_rigidKinematic->_rigidbody->SetFlag(Engine::Physics::CollisionType::Trigger, false);
	_rigidKinematic->_rigidbody->SetFlag(Engine::Physics::CollisionType::Scene_Query, true);

	PhysicsManager->CreateStaticBoundBoxActor(&_rigidKinematic->_boundBox, _boxScale, _transform);
	_rigidKinematic->_boundBox->SetOwner(this);
	PhysicsManager->GetScene(static_cast<unsigned int>(SceneFillter::cameraScene))->AddActor(_rigidKinematic->_boundBox);

	_sync->AddCallback((short)PacketID::PickObject, &Obj_Hide_Box::RemoteGrabbed, this);
	_sync->AddCallback((short)PacketID::PutObject, &Obj_Hide_Box::RemotePutThis, this);
}
