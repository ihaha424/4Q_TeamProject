#include "pch.h"
#include "PHIRigidKinematicComponent.h"

namespace Engine::PHI
{
	/********************************
				Rigid Object
	*********************************/

	void RigidKinematicComponent::SetTranslate(const Math::Vector3& position)
	{
		object->SetTranslate({ position.x, position.y, position.z });
	}
	const Math::Vector3 RigidKinematicComponent::GetTranslate() const
	{
		return Math::Vector3(object->GetTranslate());
	}
	void RigidKinematicComponent::SetRotation(const Math::Quaternion& Rotation)
	{
		object->SetRotation({ Rotation.x, Rotation.y, Rotation.z, Rotation.w });
	}
	const Math::Quaternion RigidKinematicComponent::GetRotation() const
	{
		return Math::Quaternion(object->GetRotation());
	}
	void RigidKinematicComponent::SetTransform(const Transform& transform)
	{
		object->SetTransform({ { transform.position.x, transform.position.y, transform.position.z },
			{ transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w} });
	}
	const Transform RigidKinematicComponent::GetTransform() const
	{
		auto transform = object->GetTransform();
		return Transform({ transform.position, transform.rotation, {1,1,1} });
	}
	void* RigidKinematicComponent::GetPhysicsObject() const
	{
		return object;
	}



	/********************************
			Rigid Dynamic
			Transform Associate
	*********************************/
	void RigidKinematicComponent::SetVelocity(const Engine::Math::Vector3& velocity)
	{
		object->SetVelocity({ velocity.x, velocity.y, velocity.z });
	}

	const Engine::Math::Vector3 RigidKinematicComponent::GetVelocity() const
	{
		return Math::Vector3(object->GetVelocity());
	}

	void RigidKinematicComponent::SetLinearVelocity(const Engine::Math::Vector3& velocity)
	{
		object->SetLinearVelocity({ velocity.x, velocity.y, velocity.z });
	}

	const Engine::Math::Vector3 RigidKinematicComponent::GetLinearVelocity() const
	{
		return Math::Vector3(object->GetLinearVelocity());
	}

	void RigidKinematicComponent::SetMaxLinearVelocity(const float velocity)
	{
		object->SetMaxLinearVelocity(velocity);
	}

	const float RigidKinematicComponent::GetMaxLinearVelocity() const
	{
		return object->GetMaxLinearVelocity();
	}

	void RigidKinematicComponent::SetAngularVelocity(const Engine::Math::Vector3& angularVelocity)
	{
		object->SetAngularVelocity({ angularVelocity.x, angularVelocity.y, angularVelocity.z });
	}

	const Engine::Math::Vector3 RigidKinematicComponent::GetAngularVelocity() const
	{
		return object->GetAngularVelocity();
	}

	void RigidKinematicComponent::SetMaxAngularVelocity(const float velocity)
	{
		object->SetMaxAngularVelocity(velocity);
	}

	const float RigidKinematicComponent::GetMaxAngularVelocity() const
	{
		return object->GetMaxAngularVelocity();
	}


	/********************************
			Rigid Dynamic
			Force Associate
	*********************************/
	void RigidKinematicComponent::AddForce(const Engine::Math::Vector3& force)
	{
		object->AddForce({ force.x, force.y, force.z });
	}

	void RigidKinematicComponent::AddTorque(const Engine::Math::Vector3& force)
	{
		object->AddTorque({ force.x, force.y, force.z });
	}

	void RigidKinematicComponent::ClearForce()
	{
		object->ClearForce();
	}

	void RigidKinematicComponent::ClearTorque()
	{
		object->ClearTorque();
	}



	/********************************
			Rigid Dynamic
			State Associate
	*********************************/
	void RigidKinematicComponent::Wakeup()
	{
		object->Wakeup();
	}

	bool RigidKinematicComponent::IsSleeping()
	{
		return 	object->IsSleeping();
	}

	void RigidKinematicComponent::PutToSleep()
	{
		object->PutToSleep();
	}

	void RigidKinematicComponent::SetSleepThreshold()
	{
		object->SetSleepThreshold();
	}

	void RigidKinematicComponent::SetWakeCounter(float timer)
	{
		object->SetWakeCounter(timer);
	}

	float RigidKinematicComponent::GetWakeCounter()
	{
		return object->GetWakeCounter();
	}


	/********************************
				   Shape
	*********************************/
	void RigidKinematicComponent::SetFlag(Physics::CollisionType flag, bool value)
	{
		shape->SetFlag(static_cast<PhysicsEngineAPI::Utils::DataStructure::CollisionType>(flag), value);
	}
	void RigidKinematicComponent::SetLocalTranslate(const Math::Vector3& LocalTranslate)
	{
		shape->SetLocalTranslate({ LocalTranslate.x, LocalTranslate.y, LocalTranslate.z });
	}
	const Math::Vector3 RigidKinematicComponent::GetLocalTranslate() const
	{
		return Math::Vector3(shape->GetLocalTranslate());
	}
	void RigidKinematicComponent::SetLocalRotation(const Math::Quaternion& LocalRotation)
	{
		shape->SetLocalRotation({ LocalRotation.x, LocalRotation.y, LocalRotation.z, LocalRotation.w });
	}
	const Math::Quaternion RigidKinematicComponent::GetLocalRotation() const
	{
		return Math::Quaternion(shape->GetLocalRotation());
	}
	void RigidKinematicComponent::SetLocalTransform(const Transform& LocalTransform)
	{
		shape->SetLocalTransform({ { LocalTransform.position.x, LocalTransform.position.y, LocalTransform.position.z },
			{ LocalTransform.rotation.x, LocalTransform.rotation.y, LocalTransform.rotation.z, LocalTransform.rotation.w} });
	}
	const Transform RigidKinematicComponent::GetLocalTransform() const
	{
		auto transform = shape->GetLocalTransform();
		return Transform({ transform.position, transform.rotation, {1,1,1} });
	}
	void RigidKinematicComponent::SetScale(const Math::Vector3& Scale)
	{
		shape->SetScale({ Scale.x, Scale.y, Scale.z });
	}
	const Math::Vector3 RigidKinematicComponent::GetScale() const
	{
		return Math::Vector3(shape->GetScale());
	}

	/********************************
				Geometry
	*********************************/
	void RigidKinematicComponent::SetType(Physics::GeometryShape type)
	{
		geometry->SetType(static_cast<PhysicsEngineAPI::Utils::DataStructure::GeometryShape>(type));
	}
	Physics::GeometryShape RigidKinematicComponent::GetType()
	{
		return static_cast<Physics::GeometryShape>(geometry->GetType());
	}
	const void* RigidKinematicComponent::GetGeometry() const
	{
		return geometry;
	}

	/********************************
			Engine Life Cycle
	*********************************/
	void RigidKinematicComponent::Initialize()
	{
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
	}
	void RigidKinematicComponent::Update(float deltaTime) const
	{
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
	}
	void RigidKinematicComponent::Finalize()
	{
		constexpr Utility::SafeRelease releaser;

		releaser(&object);
		releaser(&shape);
		releaser(&geometry);
		releaser(&material);
	}

}