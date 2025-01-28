#include "pch.h"
#include "PhysXActor.h"


using namespace  PhysicsEngineAPI::Utils::DataStructure;
namespace PhysicsEngineAPI
{
	PhysXActor::PhysXActor(physx::PxRigidActor* _actor)
		: actor{ _actor }
	{}
	PhysXActor::~PhysXActor() { Release(); }
	void PhysXActor::Release() { function.Release(actor); }

	void* PhysXActor::GetPhysicsObject()
	{
		return actor;
	}

	void PhysXActor::SetTranslate(const Utils::Math::Vector3& position)
	{
		function.SetTranslate(position, actor);
	}
	const Utils::Math::Vector3 PhysXActor::GetTranslate() const
	{
		return function.GetTranslate(actor);
	}

	void PhysXActor::SetRotation(const Utils::Math::Vector4& Rotation)
	{
		return function.SetRotation(Rotation, actor);
	}
	const Utils::Math::Vector4 PhysXActor::GetRotation() const
	{
		return function.GetRotation(actor);
	}

	void PhysXActor::SetTransform(const Utils::Math::Transform& _transform)
	{
		return function.SetTransform(_transform, actor);
	}
	const Utils::Math::Transform PhysXActor::GetTransform() const
	{
		return function.GetTransform(actor);
	}

	void PhysXActor::SetName(const char* name)
	{
		return function.SetName(name, actor);
	}

	const char* PhysXActor::GetName() const
	{
		return function.GetName(actor);
	}

	void PhysXActor::SetUserData(ICollision* _userData)
	{
		function.SetUserData(_userData, actor);
	}

	void PhysXActor::ClearUserData()
	{
		function.ClearUserData(actor);
	}

	const ICollision* PhysXActor::GetUserData() const
	{
		return function.GetUserData(actor);
	}

	bool PhysXActor::AttachShape(IShape* _shape)
	{
		return function.AttachShape(_shape, actor);
	}
	bool PhysXActor::DetachShape(IShape* _shape)
	{
		return function.DetachShape(_shape, actor);
	}
}