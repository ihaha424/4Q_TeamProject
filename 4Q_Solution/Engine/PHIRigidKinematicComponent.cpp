#include "pch.h"
#include "PHIRigidKinematicComponent.h"
#include "PHICoordinateConvert.h"

using namespace Engine::PHI::CONVERT;
namespace Engine::PHI
{
	RigidKinematicComponent::RigidKinematicComponent()
		: object{ nullptr }
		, shape{ nullptr }
		, geometry{ nullptr }
		, material{ nullptr }
	{
		collision = new Collision<RigidKinematicComponent>{ this };
	}

	/********************************
				Rigid Object
	*********************************/

	void RigidKinematicComponent::SetTranslate(const Math::Vector3& position)
	{
		object->SetTranslate(Vector3ToPhysicsVector3(position));
	}
	const Math::Vector3 RigidKinematicComponent::GetTranslate() const
	{
		return PhysicsVector3ToVector3(object->GetTranslate());
	}
	void RigidKinematicComponent::SetRotation(const Math::Quaternion& Rotation)
	{
		object->SetRotation(QuaternionToPhysicsVector4(Rotation));
	}
	const Math::Quaternion RigidKinematicComponent::GetRotation() const
	{
		return PhysicsVector4ToQuaternion(object->GetRotation());
	}
	void RigidKinematicComponent::SetTransform(const Transform& transform)
	{
		object->SetTransform(TransformToPhysicsTransform(transform));
	}
	const Transform RigidKinematicComponent::GetTransform() const
	{
		return PhysicsTransformToTransform(object->GetTransform());
	}




	/********************************
			Rigid Dynamic
			Transform Associate
	*********************************/
	void RigidKinematicComponent::SetVelocity(const Engine::Math::Vector3& velocity)
	{
		object->SetVelocity(Vector3ToPhysicsVector3(velocity));
	}

	const Engine::Math::Vector3 RigidKinematicComponent::GetVelocity() const
	{
		return PhysicsVector3ToVector3(object->GetVelocity());
	}

	void RigidKinematicComponent::SetLinearVelocity(const Engine::Math::Vector3& velocity)
	{
		object->SetLinearVelocity(Vector3ToPhysicsVector3(velocity));
	}

	const Engine::Math::Vector3 RigidKinematicComponent::GetLinearVelocity() const
	{
		return PhysicsVector3ToVector3(object->GetLinearVelocity());
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
		object->SetAngularVelocity(Vector3ToPhysicsVector3(angularVelocity));
	}

	const Engine::Math::Vector3 RigidKinematicComponent::GetAngularVelocity() const
	{
		return PhysicsVector3ToVector3(object->GetAngularVelocity());
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
		object->AddForce(Vector3ToPhysicsVector3(force));
	}

	void RigidKinematicComponent::AddTorque(const Engine::Math::Vector3& force)
	{
		object->AddTorque(Vector3ToPhysicsVector3(force));
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
		shape->SetLocalTranslate(Vector3ToPhysicsVector3(LocalTranslate));
	}
	const Math::Vector3 RigidKinematicComponent::GetLocalTranslate() const
	{
		return PhysicsVector3ToVector3(shape->GetLocalTranslate());
	}
	void RigidKinematicComponent::SetLocalRotation(const Math::Quaternion& LocalRotation)
	{
		shape->SetLocalRotation(QuaternionToPhysicsVector4(LocalRotation));
	}
	const Math::Quaternion RigidKinematicComponent::GetLocalRotation() const
	{
		return PhysicsVector4ToQuaternion(shape->GetLocalRotation());
	}
	void RigidKinematicComponent::SetLocalTransform(const Transform& LocalTransform)
	{
		shape->SetLocalTransform(TransformToPhysicsTransform(LocalTransform));
	}
	const Transform RigidKinematicComponent::GetLocalTransform() const
	{
		return PhysicsTransformToTransform(shape->GetLocalTransform());
	}
	void RigidKinematicComponent::SetScale(const Math::Vector3& Scale)
	{
		shape->SetScale(Vector3ToPhysicsVector3(Scale));
	}
	const Math::Vector3 RigidKinematicComponent::GetScale() const
	{
		return PhysicsVector3ToVector3(shape->GetScale());
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


	/********************************
			Engine Life Cycle
	*********************************/
	void RigidKinematicComponent::Initialize(Engine::Component::Component* Owner)
	{
		owner = static_cast<Engine::Component::RigidKinematic*>(Owner);
		object->SetUserData(collision);
		if (nullptr != shape) shape->SetUserData(collision);
	}
	void RigidKinematicComponent::Update(float deltaTime) const
	{
		collision->FixedUpdate();
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
		// TODO
	}

	void RigidKinematicComponent::FixedUpdate() const
	{
		collision->FixedUpdate();
	}

	void RigidKinematicComponent::Finalize()
	{
		constexpr Utility::SafeRelease releaser;

		releaser(&object);
		releaser(&shape);
		releaser(&geometry);
		releaser(&material);
		releaser(&collision);
	}

	Engine::Object* RigidKinematicComponent::GetOwner()
	{
		return owner->GetOwner();
	}

	void RigidKinematicComponent::BindCollision(const Physics::CallBackTrigger& callback, Physics::TriggerType type)
	{
		collision->BindCollision(callback, type);
	}
	void RigidKinematicComponent::BindCollision(const Physics::CallBackContact& callback, Physics::ContactType type)
	{
		collision->BindCollision(callback, type);
	}
}