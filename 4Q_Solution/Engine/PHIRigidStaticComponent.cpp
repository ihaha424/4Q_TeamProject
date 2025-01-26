#include "pch.h"
#include "PHIRigidStaticComponent.h"


namespace Engine::PHI
{
	/********************************
				Rigid Object
	*********************************/

	void RigidStaticComponent::SetTranslate(const Math::Vector3& position)
	{
		object->SetTranslate({ position.x, position.y, position.z });
	}
	const Math::Vector3 RigidStaticComponent::GetTranslate() const
	{
		return Math::Vector3(object->GetTranslate());
	}
	void RigidStaticComponent::SetRotation(const Math::Quaternion& Rotation)
	{
		object->SetRotation({ Rotation.x, Rotation.y, Rotation.z, Rotation.w });
	}
	const Math::Quaternion RigidStaticComponent::GetRotation() const
	{
		return Math::Quaternion(object->GetRotation());
	}
	void RigidStaticComponent::SetTransform(const Transform& transform)
	{
		object->SetTransform({ { transform.position.x, transform.position.y, transform.position.z },
			{ transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w} });
	}
	const Transform RigidStaticComponent::GetTransform() const
	{
		auto transform = object->GetTransform();
		return Transform({ transform.position, transform.rotation, {1,1,1} });
	}
	void* RigidStaticComponent::GetPhysicsObject() const
	{
		return object;
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
		shape->SetLocalTranslate({ LocalTranslate.x, LocalTranslate.y, LocalTranslate.z });
	}
	const Math::Vector3 RigidStaticComponent::GetLocalTranslate() const
	{
		return Math::Vector3(shape->GetLocalTranslate());
	}
	void RigidStaticComponent::SetLocalRotation(const Math::Quaternion& LocalRotation)
	{
		shape->SetLocalRotation({ LocalRotation.x, LocalRotation.y, LocalRotation.z, LocalRotation.w });
	}
	const Math::Quaternion RigidStaticComponent::GetLocalRotation() const
	{
		return Math::Quaternion(shape->GetLocalRotation());
	}
	void RigidStaticComponent::SetLocalTransform(const Transform& LocalTransform)
	{
		shape->SetLocalTransform({ { LocalTransform.position.x, LocalTransform.position.y, LocalTransform.position.z },
			{ LocalTransform.rotation.x, LocalTransform.rotation.y, LocalTransform.rotation.z, LocalTransform.rotation.w} });
	}
	const Transform RigidStaticComponent::GetLocalTransform() const
	{
		auto transform = shape->GetLocalTransform();
		return Transform({ transform.position, transform.rotation, {1,1,1} });
	}
	void RigidStaticComponent::SetScale(const Math::Vector3& Scale)
	{
		shape->SetScale({ Scale.x, Scale.y, Scale.z });
	}
	const Math::Vector3 RigidStaticComponent::GetScale() const
	{
		return Math::Vector3(shape->GetScale());
	}

	void* RigidStaticComponent::GetShape() const
	{
		return shape;
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
	void* RigidStaticComponent::GetGeometry() const
	{
		return geometry;
	}

	/********************************
			Engine Life Cycle
	*********************************/
	void RigidStaticComponent::Initialize()
	{
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
	}
	void RigidStaticComponent::Update(float deltaTime) const
	{
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
	}
	void RigidStaticComponent::Finalize()
	{
		constexpr Utility::SafeRelease releaser;

		releaser(&object);
		releaser(&shape);
		releaser(&geometry);
		releaser(&material);
	}
}
