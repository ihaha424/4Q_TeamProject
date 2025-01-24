#include "pch.h"
#include "PhysXKinematicActor.h"

namespace PhysicsEngineAPI
{
	PhysXKinematicActor::PhysXKinematicActor(physx::PxRigidDynamic* _actor) 
		: actor{ _actor }
	{}
	PhysXKinematicActor::~PhysXKinematicActor() { Release(); }

	void PhysXKinematicActor::Release() { function.Release(actor); }

	/*******************************************************************
	PhysXDynamic
	*********************************************************************/
	void PhysXKinematicActor::SetVelocity(const Utils::Math::Vector3& velocity)
	{
		function.SetVelocity(velocity, actor);
	}
	const Utils::Math::Vector3 PhysXKinematicActor::GetVelocity() const
	{
		return function.GetVelocity(actor);
	}
	void PhysXKinematicActor::SetLinearVelocity(const Utils::Math::Vector3& velocity)
	{
		function.SetLinearVelocity(velocity, actor);
	}
	const Utils::Math::Vector3 PhysXKinematicActor::GetLinearVelocity() const
	{
		return function.GetLinearVelocity(actor);
	}
	void PhysXKinematicActor::SetMaxLinearVelocity(const float velocity)
	{
		return function.SetMaxLinearVelocity(velocity, actor);
	}
	const float PhysXKinematicActor::GetMaxLinearVelocity() const
	{
		return function.GetMaxLinearVelocity(actor);
	}
	void PhysXKinematicActor::SetAngularVelocity(const Utils::Math::Vector3& angularVelocity)
	{
		function.SetAngularVelocity(angularVelocity, actor);
	}
	const Utils::Math::Vector3 PhysXKinematicActor::GetAngularVelocity() const
	{
		return function.GetAngularVelocity(actor);
	}
	void PhysXKinematicActor::SetMaxAngularVelocity(const float velocity)
	{
		function.SetMaxAngularVelocity(velocity, actor);
	}
	const float PhysXKinematicActor::GetMaxAngularVelocity() const
	{
		return function.GetMaxAngularVelocity(actor);
	}
	void PhysXKinematicActor::Wakeup()
	{
		function.Wakeup(actor);
	}
	bool PhysXKinematicActor::IsSleeping()
	{
		return function.IsSleeping(actor);
	}
	void PhysXKinematicActor::PutToSleep()
	{
		function.PutToSleep(actor);
	}
	void PhysXKinematicActor::SetSleepThreshold()
	{
		function.SetSleepThreshold(actor);
	}
	void PhysXKinematicActor::SetWakeCounter(float timer)
	{
		function.SetWakeCounter(timer, actor);
	}
	float PhysXKinematicActor::GetWakeCounter()
	{
		return function.GetWakeCounter(actor);
	}

	void PhysXKinematicActor::AddForce(const Utils::Math::Vector3& force)
	{
		function.AddForce(force, actor);
	}
	void PhysXKinematicActor::AddTorque(const Utils::Math::Vector3& force)
	{
		function.AddTorque(force, actor);
	}
	void PhysXKinematicActor::ClearForce()
	{
		function.ClearForce(actor);
	}
	void PhysXKinematicActor::ClearTorque()
	{
		function.ClearTorque(actor);
	}












	/*******************************************************************
	PhysXActor
	*********************************************************************/

	void PhysXKinematicActor::SetTranslate(const Utils::Math::Vector3& position)
	{
		function.SetTranslate(position, actor);
	}
	const Utils::Math::Vector3 PhysXKinematicActor::GetTranslate() const
	{
		return function.GetTranslate(actor);
	}

	void PhysXKinematicActor::SetRotation(const Utils::Math::Vector4& Rotation)
	{
		return function.SetRotation(Rotation, actor);
	}
	const Utils::Math::Vector4 PhysXKinematicActor::GetRotation() const
	{
		return function.GetRotation(actor);
	}

	void PhysXKinematicActor::SetTransform(const Utils::Math::Transform& _transform)
	{
		return function.SetTransform(_transform, actor);
	}
	const Utils::Math::Transform PhysXKinematicActor::GetTransform() const
	{
		return function.GetTransform(actor);
	}

	void PhysXKinematicActor::SetName(const char* name)
	{
		return function.SetName(name, actor);
	}

	const char* PhysXKinematicActor::GetName() const
	{
		return function.GetName(actor);
	}

	void PhysXKinematicActor::SetUserData(ICollision* _userData)
	{
		function.SetUserData(_userData, actor);
	}

	void PhysXKinematicActor::ClearUserData()
	{
		function.ClearUserData(actor);
	}

	void* PhysXKinematicActor::GetPhysicsObject()
	{
		return actor;
	}

	const ICollision* PhysXKinematicActor::GetUserData() const
	{
		return function.GetUserData(actor);
	}

	bool PhysXKinematicActor::AttachShape(IShape* _shape)
	{
		return function.AttachShape(_shape, actor);
	}
	bool PhysXKinematicActor::DetachShape(IShape* _shape)
	{
		return function.DetachShape(_shape, actor);
	}
}