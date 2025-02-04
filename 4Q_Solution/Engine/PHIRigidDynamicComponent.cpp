#include "pch.h"
#include "PHIRigidDynamicComponent.h"
#include "PHICoordinateConvert.h"

using namespace Engine::PHI::CONVERT;
namespace Engine::PHI
{
	RigidDynamicComponent::RigidDynamicComponent()
		: object{ nullptr }
		, shape{ nullptr }
		, geometry{ nullptr }
		, material{ nullptr }
		, collision{ nullptr }
	{
		collision = new Collision<RigidDynamicComponent>{ this };
	}

	/********************************
				Rigid Object
	*********************************/

	void RigidDynamicComponent::SetTranslate(const Math::Vector3& position)
	{
		object->SetTranslate(Vector3ToPhysicsVector3(position));
	}
	const Math::Vector3 RigidDynamicComponent::GetTranslate() const
	{
		return PhysicsVector3ToVector3(object->GetTranslate());
	}
	void RigidDynamicComponent::SetRotation(const Math::Quaternion& Rotation)
	{
		object->SetRotation(QuaternionToPhysicsVector4(Rotation));
	}
	const Math::Quaternion RigidDynamicComponent::GetRotation() const
	{
		return PhysicsVector4ToQuaternion(object->GetRotation());
	}
	void RigidDynamicComponent::SetTransform(const Transform& transform)
	{
		object->SetTransform(TransformToPhysicsTransform(transform));
	}
	const Transform RigidDynamicComponent::GetTransform() const
	{
		return PhysicsTransformToTransform(object->GetTransform());
	}



	/********************************
			Rigid Dynamic
			Transform Associate
	*********************************/
	void RigidDynamicComponent::SetVelocity(const Engine::Math::Vector3& velocity)
	{
		object->SetVelocity(Vector3ToPhysicsVector3(velocity));
	}

	const Engine::Math::Vector3 RigidDynamicComponent::GetVelocity() const
	{
		return PhysicsVector3ToVector3(object->GetVelocity());
	}

	void RigidDynamicComponent::SetLinearVelocity(const Engine::Math::Vector3& velocity)
	{
		object->SetLinearVelocity(Vector3ToPhysicsVector3(velocity));
	}

	const Engine::Math::Vector3 RigidDynamicComponent::GetLinearVelocity() const
	{
		return PhysicsVector3ToVector3(object->GetLinearVelocity());
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
		object->SetAngularVelocity(Vector3ToPhysicsVector3(angularVelocity));
	}

	const Engine::Math::Vector3 RigidDynamicComponent::GetAngularVelocity() const
	{
		return PhysicsVector3ToVector3(object->GetAngularVelocity());
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
		object->AddForce(Vector3ToPhysicsVector3(force));
	}

	void RigidDynamicComponent::AddTorque(const Engine::Math::Vector3& force)
	{
		object->AddTorque(Vector3ToPhysicsVector3(force));
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
		shape->SetLocalTranslate(Vector3ToPhysicsVector3(LocalTranslate));
	}
	const Math::Vector3 RigidDynamicComponent::GetLocalTranslate() const
	{
		return PhysicsVector3ToVector3(shape->GetLocalTranslate());
	}
	void RigidDynamicComponent::SetLocalRotation(const Math::Quaternion& LocalRotation)
	{
		shape->SetLocalRotation(QuaternionToPhysicsVector4(LocalRotation));
	}
	const Math::Quaternion RigidDynamicComponent::GetLocalRotation() const
	{
		return PhysicsVector4ToQuaternion(shape->GetLocalRotation());
	}
	void RigidDynamicComponent::SetLocalTransform(const Transform& LocalTransform)
	{
		shape->SetLocalTransform(TransformToPhysicsTransform(LocalTransform));
	}
	const Transform RigidDynamicComponent::GetLocalTransform() const
	{
		return PhysicsTransformToTransform(shape->GetLocalTransform());
	}
	void RigidDynamicComponent::SetScale(const Math::Vector3& Scale)
	{
		shape->SetScale(Vector3ToPhysicsVector3(Scale));
	}
	const Math::Vector3 RigidDynamicComponent::GetScale() const
	{
		return PhysicsVector3ToVector3(shape->GetScale());
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
		object->SetUserData(collision);
		if (nullptr != shape) shape->SetUserData(collision);
	}
	void RigidDynamicComponent::Update(float deltaTime) const
	{
		collision->FixedUpdate();
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
	}

	void RigidDynamicComponent::FixedUpdate() const
	{
		collision->FixedUpdate();
	}

	void RigidDynamicComponent::Finalize()
	{
		constexpr Utility::SafeRelease releaser;

		releaser(&object);
		releaser(&shape);
		releaser(&geometry);
		releaser(&material);
		releaser(&collision);
	}

	void* RigidDynamicComponent::GetOwner()
	{
		return owner->GetOwner();
	}

	void RigidDynamicComponent::BindCollision(const Physics::CallBackTrigger& callback, Physics::TriggerType type)
	{
		collision->BindCollision(callback, type);
	}
	void RigidDynamicComponent::BindCollision(const Physics::CallBackContact& callback, Physics::ContactType type)
	{
		collision->BindCollision(callback, type);
	}
}