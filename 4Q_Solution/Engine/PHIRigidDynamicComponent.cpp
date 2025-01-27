#include "pch.h"
#include "PHIRigidDynamicComponent.h"

namespace Engine::PHI
{
	RigidDynamicComponent::RigidDynamicComponent()
		: object{ nullptr }
		, shape{ nullptr }
		, geometry{ nullptr }
		, material{ nullptr }
	{
	}

	/********************************
				Rigid Object
	*********************************/

	void RigidDynamicComponent::SetTranslate(const Math::Vector3& position)
	{
		object->SetTranslate({ position.x, position.y, position.z });
	}
	const Math::Vector3 RigidDynamicComponent::GetTranslate() const
	{
		return Math::Vector3(object->GetTranslate());
	}
	void RigidDynamicComponent::SetRotation(const Math::Quaternion& Rotation)
	{
		object->SetRotation({ Rotation.x, Rotation.y, Rotation.z, Rotation.w });
	}
	const Math::Quaternion RigidDynamicComponent::GetRotation() const
	{
		return Math::Quaternion(object->GetRotation());
	}
	void RigidDynamicComponent::SetTransform(const Transform& transform)
	{
		object->SetTransform({ { transform.position.x, transform.position.y, transform.position.z },
			{ transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w} });
	}
	const Transform RigidDynamicComponent::GetTransform() const
	{
		auto transform = object->GetTransform();
		return Transform({ transform.position, transform.rotation, {1,1,1} });
	}



	/********************************
			Rigid Dynamic
			Transform Associate
	*********************************/
	void RigidDynamicComponent::SetVelocity(const Engine::Math::Vector3& velocity)
	{
		object->SetVelocity({ velocity.x, velocity.y, velocity.z });
	}

	const Engine::Math::Vector3 RigidDynamicComponent::GetVelocity() const
	{
		return Math::Vector3(object->GetVelocity());
	}

	void RigidDynamicComponent::SetLinearVelocity(const Engine::Math::Vector3& velocity)
	{
		object->SetLinearVelocity({ velocity.x, velocity.y, velocity.z });
	}

	const Engine::Math::Vector3 RigidDynamicComponent::GetLinearVelocity() const
	{
		return Math::Vector3(object->GetLinearVelocity());
	}

	void RigidDynamicComponent::SetMaxLinearVelocity(const float velocity)
	{
		object->SetMaxLinearVelocity(velocity);
	}

	const float RigidDynamicComponent::GetMaxLinearVelocity() const
	{
		return object->GetMaxLinearVelocity();
	}

	void RigidDynamicComponent::SetAngularVelocity(const Engine::Math::Vector3& angularVelocity)
	{
		object->SetAngularVelocity({ angularVelocity.x, angularVelocity.y, angularVelocity.z });
	}

	const Engine::Math::Vector3 RigidDynamicComponent::GetAngularVelocity() const
	{
		return object->GetAngularVelocity();
	}

	void RigidDynamicComponent::SetMaxAngularVelocity(const float velocity)
	{
		object->SetMaxAngularVelocity(velocity);
	}

	const float RigidDynamicComponent::GetMaxAngularVelocity() const
	{
		return object->GetMaxAngularVelocity();
	}


	/********************************
			Rigid Dynamic
			Force Associate
	*********************************/
	void RigidDynamicComponent::AddForce(const Engine::Math::Vector3& force)
	{
		object->AddForce({ force.x, force.y, force.z });
	}

	void RigidDynamicComponent::AddTorque(const Engine::Math::Vector3& force)
	{
		object->AddTorque({ force.x, force.y, force.z });
	}

	void RigidDynamicComponent::ClearForce()
	{
		object->ClearForce();
	}

	void RigidDynamicComponent::ClearTorque()
	{
		object->ClearTorque();
	}



	/********************************
			Rigid Dynamic
			State Associate
	*********************************/
	void RigidDynamicComponent::Wakeup()
	{
		object->Wakeup();
	}

	bool RigidDynamicComponent::IsSleeping()
	{
		return 	object->IsSleeping();
	}

	void RigidDynamicComponent::PutToSleep()
	{
		object->PutToSleep();
	}

	void RigidDynamicComponent::SetSleepThreshold()
	{
		object->SetSleepThreshold();
	}

	void RigidDynamicComponent::SetWakeCounter(float timer)
	{
		object->SetWakeCounter(timer);
	}

	float RigidDynamicComponent::GetWakeCounter()
	{
		return object->GetWakeCounter();
	}


	/********************************
				   Shape
	*********************************/
	void RigidDynamicComponent::SetFlag(Physics::CollisionType flag, bool value)
	{
		shape->SetFlag(static_cast<PhysicsEngineAPI::Utils::DataStructure::CollisionType>(flag), value);
	}
	void RigidDynamicComponent::SetLocalTranslate(const Math::Vector3& LocalTranslate)
	{
		shape->SetLocalTranslate({ LocalTranslate.x, LocalTranslate.y, LocalTranslate.z });
	}
	const Math::Vector3 RigidDynamicComponent::GetLocalTranslate() const
	{
		return Math::Vector3(shape->GetLocalTranslate());
	}
	void RigidDynamicComponent::SetLocalRotation(const Math::Quaternion& LocalRotation)
	{
		shape->SetLocalRotation({ LocalRotation.x, LocalRotation.y, LocalRotation.z, LocalRotation.w });
	}
	const Math::Quaternion RigidDynamicComponent::GetLocalRotation() const
	{
		return Math::Quaternion(shape->GetLocalRotation());
	}
	void RigidDynamicComponent::SetLocalTransform(const Transform& LocalTransform)
	{
		shape->SetLocalTransform({ { LocalTransform.position.x, LocalTransform.position.y, LocalTransform.position.z },
			{ LocalTransform.rotation.x, LocalTransform.rotation.y, LocalTransform.rotation.z, LocalTransform.rotation.w} });
	}
	const Transform RigidDynamicComponent::GetLocalTransform() const
	{
		auto transform = shape->GetLocalTransform();
		return Transform({ transform.position, transform.rotation, {1,1,1} });
	}
	void RigidDynamicComponent::SetScale(const Math::Vector3& Scale)
	{
		shape->SetScale({ Scale.x, Scale.y, Scale.z });
	}
	const Math::Vector3 RigidDynamicComponent::GetScale() const
	{
		return Math::Vector3(shape->GetScale());
	}


	/********************************
				Geometry
	*********************************/
	void RigidDynamicComponent::SetType(Physics::GeometryShape type)
	{
		geometry->SetType(static_cast<PhysicsEngineAPI::Utils::DataStructure::GeometryShape>(type));
	}
	Physics::GeometryShape RigidDynamicComponent::GetType()
	{
		return static_cast<Physics::GeometryShape>(geometry->GetType());
	}

	/********************************
			Engine Life Cycle
	*********************************/
	void RigidDynamicComponent::Initialize()
	{
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
	}
	void RigidDynamicComponent::Update(float deltaTime) const
	{
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
	}
	void RigidDynamicComponent::Finalize()
	{
		constexpr Utility::SafeRelease releaser;

		releaser(&object);
		releaser(&shape);
		releaser(&geometry);
		releaser(&material);
	}
	
}