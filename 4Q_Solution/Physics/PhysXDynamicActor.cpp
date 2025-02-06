#include "pch.h"
#include "PhysXDynamicActor.h"

namespace PhysicsEngineAPI
{
	PhysXDynamicActor::PhysXDynamicActor(physx::PxRigidDynamic* _actor)
		: actor{ _actor }
	{}
	PhysXDynamicActor::~PhysXDynamicActor() { Release(); }
	void PhysXDynamicActor::Release() { function.Release(actor); }

	/*******************************************************************
	PhysXDynamic
	*********************************************************************/
	void PhysXDynamicActor::SetVelocity(const Utils::Math::Vector3& velocity) 
	{
		function.SetVelocity(velocity, actor);
	}
	 Utils::Math::Vector3 PhysXDynamicActor::GetVelocity() const
	{
		return function.GetVelocity(actor);
	}
	void PhysXDynamicActor::SetLinearVelocity(const Utils::Math::Vector3& velocity) 
	{
		function.SetLinearVelocity(velocity, actor);
	}
	 Utils::Math::Vector3 PhysXDynamicActor::GetLinearVelocity() const
	{
		return function.GetLinearVelocity(actor);
	}
	void PhysXDynamicActor::SetMaxLinearVelocity(const float velocity) 
	{
		return function.SetMaxLinearVelocity(velocity, actor);
	}
	 float PhysXDynamicActor::GetMaxLinearVelocity() const
	{
		return function.GetMaxLinearVelocity(actor);
	}
	void PhysXDynamicActor::SetAngularVelocity(const Utils::Math::Vector3& angularVelocity) 
	{
		function.SetAngularVelocity(angularVelocity, actor);
	}
	 Utils::Math::Vector3 PhysXDynamicActor::GetAngularVelocity() const
	{
		return function.GetAngularVelocity(actor);
	}
	void PhysXDynamicActor::SetMaxAngularVelocity(const float velocity) 
	{
		function.SetMaxAngularVelocity(velocity, actor);
	}
	 float PhysXDynamicActor::GetMaxAngularVelocity() const
	{
		return function.GetMaxAngularVelocity(actor);
	}
	void PhysXDynamicActor::Wakeup() 
	{
		function.Wakeup(actor);
	}
	bool PhysXDynamicActor::IsSleeping() 
	{
		return function.IsSleeping(actor);
	}
	void PhysXDynamicActor::PutToSleep() 
	{
		function.PutToSleep(actor);
	}
	void PhysXDynamicActor::SetSleepThreshold() 
	{
		function.SetSleepThreshold(actor);
	}
	void PhysXDynamicActor::SetWakeCounter(float timer) 
	{
		function.SetWakeCounter(timer, actor);
	}
	float PhysXDynamicActor::GetWakeCounter() 
	{
		return function.GetWakeCounter(actor);
	}
			
	void PhysXDynamicActor::AddForce(const Utils::Math::Vector3& force)
	{
		function.AddForce(force, actor);
	}
	void PhysXDynamicActor::AddTorque(const Utils::Math::Vector3& force)
	{
		function.AddTorque(force, actor);
	}
	void PhysXDynamicActor::ClearForce()
	{
		function.ClearForce(actor);
	}
	void PhysXDynamicActor::ClearTorque()
	{
		function.ClearTorque(actor);
	}












	/*******************************************************************
	PhysXActor
	*********************************************************************/

	void PhysXDynamicActor::SetTranslate(const Utils::Math::Vector3& position)
	{
		function.SetTranslate(position, actor);
	}
	 Utils::Math::Vector3 PhysXDynamicActor::GetTranslate() const
	{
		return function.GetTranslate(actor);
	}

	void PhysXDynamicActor::SetRotation(const Utils::Math::Vector4& Rotation)
	{
		return function.SetRotation(Rotation, actor);
	}
	 Utils::Math::Vector4 PhysXDynamicActor::GetRotation() const
	{
		return function.GetRotation(actor);
	}

	void PhysXDynamicActor::SetTransform(const Utils::Math::Transform& _transform)
	{
		return function.SetTransform(_transform, actor);
	}
	 Utils::Math::Transform PhysXDynamicActor::GetTransform() const
	{
		return function.GetTransform(actor);
	}

	void PhysXDynamicActor::SetName(const char* name)
	{
		return function.SetName(name, actor);
	}

	const char* PhysXDynamicActor::GetName() const
	{
		return function.GetName(actor);
	}

	void PhysXDynamicActor::SetUserData(ICollision* _userData)
	{
		function.SetUserData(_userData, actor);
	}

	void PhysXDynamicActor::ClearUserData()
	{
		function.ClearUserData(actor);
	}

	void* PhysXDynamicActor::GetPhysicsObject()
	{
		return actor;
	}

	const ICollision* PhysXDynamicActor::GetUserData() const
	{
		return function.GetUserData(actor);
	}

	bool PhysXDynamicActor::AttachShape(IShape* _shape)
	{
		return function.AttachShape(_shape, actor);
	}
	bool PhysXDynamicActor::DetachShape(IShape* _shape)
	{
		return function.DetachShape(_shape, actor);
	}




}