#include "pch.h"
#include "PhysXActorFunction.h"
#include "PhysXShape.h"

namespace PhysicsEngineAPI
{
	void PhysXActorFunction::Release(physx::PxRigidActor* actor) { SAFE_RELEASE(actor); }


	void PhysXActorFunction::SetTranslate(const Utils::Math::Vector3& position, physx::PxRigidActor* actor)
	{
		auto transform = actor->getGlobalPose();
		transform.p = { position.x, position.y, position.z };
		actor->setGlobalPose(transform);
	}
	 Utils::Math::Vector3 PhysXActorFunction::GetTranslate(physx::PxRigidActor* actor) const
	{
		auto transform = actor->getGlobalPose();
		return Utils::Math::Vector3({ transform.p.x, transform.p.y, transform.p.z });
	}

	void PhysXActorFunction::SetRotation(const Utils::Math::Vector4& Rotation, physx::PxRigidActor* actor)
	{
		auto transform = actor->getGlobalPose();
		transform.q = { Rotation.x, Rotation.y, Rotation.z, Rotation.w };
		actor->setGlobalPose(transform);
	}
	 Utils::Math::Vector4 PhysXActorFunction::GetRotation(physx::PxRigidActor* actor) const
	{
		auto transform = actor->getGlobalPose();
		return Utils::Math::Vector4({ transform.q.x, transform.q.y, transform.q.z, transform.q.w });
	}

	void PhysXActorFunction::SetTransform(const Utils::Math::Transform& _transform, physx::PxRigidActor* actor)
	{
		const physx::PxTransform transform
		{
			{ _transform.position.x, _transform.position.y, _transform.position.z }
			, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w}
		};
		actor->setGlobalPose(transform);
	}
	 Utils::Math::Transform PhysXActorFunction::GetTransform(physx::PxRigidActor* actor) const
	{
		auto transform = actor->getGlobalPose();
		return Utils::Math::Transform({ transform.p.x, transform.p.y, transform.p.z }, { transform.q.x, transform.q.y, transform.q.z, transform.q.w });
	}

	 Utils::Math::Vector3 PhysXActorFunction::GetBounds(physx::PxRigidActor* actor) const
	 {
		 return PxVec3ToVector3(actor->getWorldBounds().getExtents());
	 }

	void PhysXActorFunction::SetName(const char* name, physx::PxRigidActor* actor)
	{
		actor->setName(name);
	}

	const char* PhysXActorFunction::GetName(physx::PxRigidActor* actor) const
	{
		return actor->getName();
	}

	void PhysXActorFunction::SetUserData(ICollision* _userData, physx::PxRigidActor* actor)
	{
		actor->userData = _userData;
	}

	void PhysXActorFunction::ClearUserData(physx::PxRigidActor* actor)
	{
		actor->userData = nullptr;
	}

	const ICollision* PhysXActorFunction::GetUserData(physx::PxRigidActor* actor) const
	{
		return static_cast<ICollision*>(actor->userData);
	}

	bool PhysXActorFunction::AttachShape(IShape* _shape, physx::PxRigidActor* actor)
	{
		PhysXShape* shape = dynamic_cast<PhysXShape*>(_shape);
		if (nullptr == shape)
			return false;

		actor->attachShape(*(shape->shape));
		return true;
	}
	bool PhysXActorFunction::DetachShape(IShape* _shape, physx::PxRigidActor* actor)
	{
		PhysXShape* shape = dynamic_cast<PhysXShape*>(_shape);
		if (nullptr == shape)
			return false;

		actor->detachShape(*(shape->shape));
		return true;
	}
}

namespace PhysicsEngineAPI
{
	void PhysXDynamicActorFunction::SetVelocity(const Utils::Math::Vector3& velocity, physx::PxRigidDynamic* actor)
	{
		actor->setLinearVelocity({ velocity.x, velocity.y, velocity.z });
	}

	 Utils::Math::Vector3 PhysXDynamicActorFunction::GetVelocity(physx::PxRigidDynamic* actor) const
	{
		auto velocity = actor->getLinearVelocity();
		return Utils::Math::Vector3({ velocity.x, velocity.y, velocity.z });
	}

	void PhysXDynamicActorFunction::SetLinearVelocity(const Utils::Math::Vector3& velocity, physx::PxRigidDynamic* actor)
	{
		actor->setLinearVelocity({ velocity.x,velocity.y,velocity.z });
	}

	 Utils::Math::Vector3 PhysXDynamicActorFunction::GetLinearVelocity(physx::PxRigidDynamic* actor) const
	{
		auto velocity = actor->getLinearVelocity();
		return Utils::Math::Vector3({ velocity.x, velocity.y, velocity.z });
	}
	void PhysXDynamicActorFunction::SetMaxLinearVelocity(const float velocity, physx::PxRigidDynamic* actor)
	{
		actor->setMaxLinearVelocity(velocity);
	}

	 float PhysXDynamicActorFunction::GetMaxLinearVelocity(physx::PxRigidDynamic* actor) const
	{
		auto velocity = actor->getMaxLinearVelocity();
		return velocity;
	}

	void PhysXDynamicActorFunction::SetAngularVelocity(const Utils::Math::Vector3& angularVelocity, physx::PxRigidDynamic* actor)
	{
		actor->setAngularVelocity({ angularVelocity.x, angularVelocity.y, angularVelocity.z });
	}

	 Utils::Math::Vector3 PhysXDynamicActorFunction::GetAngularVelocity(physx::PxRigidDynamic* actor) const
	{
		auto angularVelocity = actor->getAngularVelocity();
		return Utils::Math::Vector3({ angularVelocity.x, angularVelocity.y, angularVelocity.z });
	}

	void PhysXDynamicActorFunction::SetMaxAngularVelocity(const float velocity, physx::PxRigidDynamic* actor)
	{
		actor->setMaxAngularVelocity(velocity);
	}

	 float PhysXDynamicActorFunction::GetMaxAngularVelocity(physx::PxRigidDynamic* actor) const
	{
		auto velocity = actor->getMaxAngularVelocity();
		return velocity;
	}

	void PhysXDynamicActorFunction::Wakeup(physx::PxRigidDynamic* actor)
	{
	}
	bool PhysXDynamicActorFunction::IsSleeping(physx::PxRigidDynamic* actor)
	{
		return false;
	}
	void PhysXDynamicActorFunction::PutToSleep(physx::PxRigidDynamic* actor)
	{
	}
	void PhysXDynamicActorFunction::SetSleepThreshold(physx::PxRigidDynamic* actor)
	{
	}
	void PhysXDynamicActorFunction::SetWakeCounter(float timer, physx::PxRigidDynamic* actor)
	{
	}
	float PhysXDynamicActorFunction::GetWakeCounter(physx::PxRigidDynamic* actor)
	{
		return 0.0f;
	}

	void PhysXDynamicActorFunction::AddForce(const Utils::Math::Vector3& force, physx::PxRigidDynamic* actor)
	{
		actor->addForce({ force.x,force.y,force.z });
	}
	void PhysXDynamicActorFunction::AddTorque(const Utils::Math::Vector3& force, physx::PxRigidDynamic* actor)
	{
		actor->addTorque({ force.x,force.y,force.z });
	}
	void PhysXDynamicActorFunction::ClearForce(physx::PxRigidDynamic* actor)
	{
		actor->clearForce();
	}
	void PhysXDynamicActorFunction::ClearTorque(physx::PxRigidDynamic* actor)
	{
		actor->clearTorque();
	}
}
