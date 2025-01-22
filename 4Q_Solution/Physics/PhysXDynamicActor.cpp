#include "pch.h"
#include "PhysXDynamicActor.h"

namespace Physics
{
	PhysXDynamicActor::PhysXDynamicActor(physx::PxRigidDynamic* actor)
		: PhysXActor(actor)
	{}
	PhysXDynamicActor::~PhysXDynamicActor()
	{}



	void PhysXDynamicActor::SetVelocity(const Utils::Math::Vector3& velocity)
	{
		physx::PxRigidDynamic* actor = reinterpret_cast<physx::PxRigidDynamic*>(this->actor);
		actor->setLinearVelocity({ velocity.x, velocity.y, velocity.z });
	}

	const Utils::Math::Vector3 PhysXDynamicActor::GetVelocity() const
	{
		physx::PxRigidDynamic* actor = reinterpret_cast<physx::PxRigidDynamic*>(this->actor);
		auto velocity = actor->getLinearVelocity();
		return Utils::Math::Vector3({ velocity.x, velocity.y, velocity.z });
	}

	void PhysXDynamicActor::SetLinearVelocity(const Utils::Math::Vector3& velocity)
	{
		physx::PxRigidDynamic* actor = reinterpret_cast<physx::PxRigidDynamic*>(this->actor);
		actor->setLinearVelocity({ velocity.x,velocity.y,velocity.z });
	}

	const Utils::Math::Vector3& PhysXDynamicActor::GetLinearVelocity() const
	{
		physx::PxRigidDynamic* actor = reinterpret_cast<physx::PxRigidDynamic*>(this->actor);
		auto velocity = actor->getLinearVelocity();
		return Utils::Math::Vector3({ velocity.x, velocity.y, velocity.z });
	}
	void PhysXDynamicActor::SetMaxLinearVelocity(const float velocity)
	{
		physx::PxRigidDynamic* actor = reinterpret_cast<physx::PxRigidDynamic*>(this->actor);
		actor->setMaxLinearVelocity(velocity);
	}

	const float PhysXDynamicActor::GetMaxLinearVelocity() const
	{
		physx::PxRigidDynamic* actor = reinterpret_cast<physx::PxRigidDynamic*>(this->actor);
		auto velocity = actor->getMaxLinearVelocity();
		return velocity;
	}

	void PhysXDynamicActor::SetAngularVelocity(const Utils::Math::Vector3& angularVelocity)
	{
		physx::PxRigidDynamic* actor = reinterpret_cast<physx::PxRigidDynamic*>(this->actor);
		actor->setAngularVelocity({ angularVelocity.x, angularVelocity.y, angularVelocity.z });
	}

	const Utils::Math::Vector3 PhysXDynamicActor::GetAngularVelocity() const
	{
		physx::PxRigidDynamic* actor = reinterpret_cast<physx::PxRigidDynamic*>(this->actor);
		auto angularVelocity = actor->getAngularVelocity();
		return Utils::Math::Vector3({ angularVelocity.x, angularVelocity.y, angularVelocity.z });
	}

	void PhysXDynamicActor::SetMaxAngularVelocity(const float velocity)
	{
		physx::PxRigidDynamic* actor = reinterpret_cast<physx::PxRigidDynamic*>(this->actor);
		actor->setMaxAngularVelocity(velocity);
	}

	const float PhysXDynamicActor::GetMaxAngularVelocity() const
	{
		physx::PxRigidDynamic* actor = reinterpret_cast<physx::PxRigidDynamic*>(this->actor);
		auto velocity = actor->getMaxAngularVelocity();
		return velocity;
	}














	void PhysXDynamicActor::Wakeup()
	{
	}
	bool PhysXDynamicActor::IsSleeping()
	{
		return false;
	}
	void PhysXDynamicActor::PutToSleep()
	{
	}
	void PhysXDynamicActor::SetSleepThreshold()
	{
	}
	void PhysXDynamicActor::SetWakeCounter(float timer)
	{
	}
	float PhysXDynamicActor::GetWakeCounter()
	{
		return 0.0f;
	}














	void PhysXDynamicActor::AddForce(const Utils::Math::Vector3& force)
	{
		physx::PxRigidDynamic* actor = reinterpret_cast<physx::PxRigidDynamic*>(this->actor);
		actor->addForce({ force.x,force.y,force.z });
	}
	void PhysXDynamicActor::AddTorque(const Utils::Math::Vector3& force)
	{
		physx::PxRigidDynamic* actor = reinterpret_cast<physx::PxRigidDynamic*>(this->actor);
		actor->addTorque({ force.x,force.y,force.z });
	}
	void PhysXDynamicActor::ClearForce()
	{
		physx::PxRigidDynamic* actor = reinterpret_cast<physx::PxRigidDynamic*>(this->actor);
		actor->clearForce();
	}
	void PhysXDynamicActor::ClearTorque()
	{
		physx::PxRigidDynamic* actor = reinterpret_cast<physx::PxRigidDynamic*>(this->actor);
		actor->clearTorque();
	}

}