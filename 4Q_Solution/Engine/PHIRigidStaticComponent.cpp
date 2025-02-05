#include "pch.h"
#include "PHIRigidStaticComponent.h"
#include "PHICoordinateConvert.h"

using namespace Engine::PHI::CONVERT;
namespace Engine::PHI
{
	RigidStaticComponent::RigidStaticComponent()
		: object{ nullptr }
		, shape{ nullptr }
		, geometry{ nullptr }
		, material{ nullptr }
		, owner{ nullptr }
	{
		collision = new Collision<RigidStaticComponent>{ this };
	}

	/********************************
				Rigid Object
	*********************************/

	void RigidStaticComponent::SetTranslate(const Math::Vector3& position)
	{
		object->SetTranslate(Vector3ToPhysicsVector3(position));
	}
	const Math::Vector3 RigidStaticComponent::GetTranslate() const
	{
		return PhysicsVector3ToVector3(object->GetTranslate());
	}
	void RigidStaticComponent::SetRotation(const Math::Quaternion& Rotation)
	{
		object->SetRotation(QuaternionToPhysicsVector4(Rotation));
	}
	const Math::Quaternion RigidStaticComponent::GetRotation() const
	{
		return PhysicsVector4ToQuaternion(object->GetRotation());
	}
	void RigidStaticComponent::SetTransform(const Transform& transform)
	{
		object->SetTransform(TransformToPhysicsTransform(transform));
	}
	const Transform RigidStaticComponent::GetTransform() const
	{
		return PhysicsTransformToTransform(object->GetTransform());
	}



	/********************************
				   Shape
	*********************************/
	void RigidStaticComponent::SetFlag(Physics::CollisionType flag, bool value)
	{
		shape->SetFlag(static_cast<PhysicsEngineAPI::Utils::DataStructure::CollisionType>(flag), value);
	}
	void RigidStaticComponent::SetLocalTranslate(const Math::Vector3& LocalTranslate)
	{
		shape->SetLocalTranslate(Vector3ToPhysicsVector3(LocalTranslate));
	}
	const Math::Vector3 RigidStaticComponent::GetLocalTranslate() const
	{
		return PhysicsVector3ToVector3(shape->GetLocalTranslate());
	}
	void RigidStaticComponent::SetLocalRotation(const Math::Quaternion& LocalRotation)
	{
		shape->SetLocalRotation(QuaternionToPhysicsVector4(LocalRotation));
	}
	const Math::Quaternion RigidStaticComponent::GetLocalRotation() const
	{
		return PhysicsVector4ToQuaternion(shape->GetLocalRotation());
	}
	void RigidStaticComponent::SetLocalTransform(const Transform& LocalTransform)
	{
		shape->SetLocalTransform(TransformToPhysicsTransform(LocalTransform));
	}
	const Transform RigidStaticComponent::GetLocalTransform() const
	{
		return PhysicsTransformToTransform(shape->GetLocalTransform());
	}
	void RigidStaticComponent::SetScale(const Math::Vector3& Scale)
	{
		shape->SetScale(Vector3ToPhysicsVector3(Scale));
	}
	const Math::Vector3 RigidStaticComponent::GetScale() const
	{
		return PhysicsVector3ToVector3(shape->GetScale());
	}



	/********************************
				Geometry
	*********************************/
	void RigidStaticComponent::SetType(Physics::GeometryShape type)
	{
		geometry->SetType(static_cast<PhysicsEngineAPI::Utils::DataStructure::GeometryShape>(type));
	}
	Physics::GeometryShape RigidStaticComponent::GetType()
	{
		return static_cast<Physics::GeometryShape>(geometry->GetType());
	}


	/********************************
			Engine Life Cycle
	*********************************/
	void RigidStaticComponent::Initialize()
	{
		object->SetUserData(collision);
		if (nullptr != shape) shape->SetUserData(collision);
	}
	void RigidStaticComponent::Update(float deltaTime) const
	{
		collision->FixedUpdate();
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
	}

	void RigidStaticComponent::FixedUpdate() const
	{
		collision->FixedUpdate();
	}

	void RigidStaticComponent::Finalize()
	{
		constexpr Utility::SafeRelease releaser;

		releaser(&object);
		releaser(&shape);
		releaser(&geometry);
		releaser(&material);
		releaser(&collision);
	}

	void* RigidStaticComponent::GetOwner()
	{
		return owner;
	}

	void RigidStaticComponent::SetOwner(void* _owner)
	{
		owner = _owner;
	}

	void RigidStaticComponent::BindCollision(const Physics::CallBackTrigger& callback, Physics::TriggerType type)
	{
		collision->BindCollision(callback, type);
	}
	void RigidStaticComponent::BindCollision(const Physics::CallBackContact& callback, Physics::ContactType type)
	{
		collision->BindCollision(callback, type);
	}
}
