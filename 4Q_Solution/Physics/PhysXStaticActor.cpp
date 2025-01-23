#include "pch.h"
#include "PhysXStaticActor.h"
#include "PhysXShape.h"

namespace PhysicsEngineAPI
{
	PhysXStaticActor::PhysXStaticActor(physx::PxRigidStatic* _actor)
		: actor{ _actor }
	{}
	PhysXStaticActor::~PhysXStaticActor() { Release(); }
	void PhysXStaticActor::Release() { function.Release(actor); }

	/*******************************************************************
	PhysXActor
	*********************************************************************/


	void PhysXStaticActor::SetTranslate(const Utils::Math::Vector3& position)
	{
		function.SetTranslate(position, actor);
	}
	const Utils::Math::Vector3 PhysXStaticActor::GetTranslate() const
	{
		return function.GetTranslate(actor);
	}

	void PhysXStaticActor::SetRotation(const Utils::Math::Vector4& Rotation)
	{
		return function.SetRotation(Rotation, actor);
	}
	const Utils::Math::Vector4 PhysXStaticActor::GetRotation() const
	{
		return function.GetRotation(actor);
	}

	void PhysXStaticActor::SetTransform(const Utils::Math::Transform& _transform)
	{
		return function.SetTransform(_transform, actor);
	}
	const Utils::Math::Transform PhysXStaticActor::GetTransform() const
	{
		return function.GetTransform(actor);
	}

	void PhysXStaticActor::SetName(const char* name)
	{
		return function.SetName(name, actor);
	}

	const char* PhysXStaticActor::GetName() const
	{
		return function.GetName(actor);
	}

	void PhysXStaticActor::SetUserData(ICollision* _userData)
	{
		function.SetUserData(_userData, actor);
	}

	void PhysXStaticActor::ClearUserData()
	{
		function.ClearUserData(actor);
	}

	void* PhysXStaticActor::GetPhysicsObject()
	{
		return actor;
	}

	const ICollision* PhysXStaticActor::GetUserData() const
	{
		return function.GetUserData(actor);
	}

	bool PhysXStaticActor::AttachShape(IShape* _shape)
	{
		return function.AttachShape(_shape, actor);
	}
	bool PhysXStaticActor::DetachShape(IShape* _shape)
	{
		return function.DetachShape(_shape, actor);
	}
}
