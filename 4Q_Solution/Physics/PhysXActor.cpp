#include "pch.h"
#include "PhysXActor.h"
#include "PhysXShape.h"

using namespace  PhysicsEngineAPI::Utils::DataStructure;
namespace PhysicsEngineAPI
{
	PhysXActor::PhysXActor(physx::PxRigidActor* _actor)
		: actor{ _actor }
	{}
	PhysXActor::~PhysXActor()
	{
		if (actor)
			actor->release();
	}
	void PhysXActor::SetTranslate(const Utils::Math::Vector3& position)
	{
		auto transform = actor->getGlobalPose();
		transform.p = { position.x, position.y, position.z };
		actor->setGlobalPose(transform);
	}
	const Utils::Math::Vector3 PhysXActor::GetTranslate() const
	{
		auto transform = actor->getGlobalPose();
		return Utils::Math::Vector3({ transform.p.x, transform.p.y, transform.p.z });
	}

	void PhysXActor::SetRotation(const Utils::Math::Vector4& Rotation)
	{
		auto transform = actor->getGlobalPose();
		transform.q = { Rotation.x, Rotation.y, Rotation.z, Rotation.w };
		actor->setGlobalPose(transform);
	}
	const Utils::Math::Vector4 PhysXActor::GetRotation() const
	{
		auto transform = actor->getGlobalPose();
		return Utils::Math::Vector4({ transform.q.x, transform.q.y, transform.q.z, transform.q.w });
	}

	void PhysXActor::SetTransform(const Utils::Math::Transform& _transform)
	{
		const physx::PxTransform transform
		{ 
			{ _transform.position.x, _transform.position.y, _transform.position.z }
			, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} 
		};
		actor->setGlobalPose(transform);
	}
	const Utils::Math::Transform PhysXActor::GetTransform() const
	{
		auto transform = actor->getGlobalPose();
		return Utils::Math::Transform({ transform.p.x, transform.p.y, transform.p.z }, { transform.q.x, transform.q.y, transform.q.z, transform.q.w });
	}

	void PhysXActor::SetName(const char* name)
	{
		actor->setName(name);
	}

	const char* PhysXActor::GetName() const
	{
		return actor->getName();
	}

	void PhysXActor::SetUserData(ICollision* _userData)
	{
		actor->userData = _userData;
	}

	void PhysXActor::ClearUserData()
	{
		actor->userData = nullptr;
	}

	void PhysXActor::Test()
	{
		physx::PxRigidDynamic* _actor = reinterpret_cast<physx::PxRigidDynamic*>(actor);
		_actor->setLinearDamping(0.5f);
	}

	const ICollision* PhysXActor::GetUserData() const
	{
		return static_cast<ICollision*>(actor->userData);
	}

	bool PhysXActor::AttachShape(IShape* _shape)
	{
		PhysXShape* shape = dynamic_cast<PhysXShape*>(_shape);
		if (nullptr == shape)
			return false;

		actor->attachShape(*(shape->shape));
		return true;
	}
	bool PhysXActor::DetachShape(IShape* _shape)
	{
		PhysXShape* shape = dynamic_cast<PhysXShape*>(_shape);
		if (nullptr == shape)
			return false;

		actor->detachShape(*(shape->shape));
		return true;
	}
}