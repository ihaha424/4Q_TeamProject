#include "pch.h"
#include "PHIRigidComponent.h"
#include "PHICoordinateConvert.h"

using namespace Engine::PHI::CONVERT;
namespace Engine::PHI
{
	RigidComponent::RigidComponent()
		: object{ nullptr }
		, shape{ nullptr }
		, geometry{ nullptr }
		, material{ nullptr }
		, collision{ nullptr }
	{
		collision = new Collision<RigidComponent>{ this };
	}

	/********************************
				Rigid Object
	*********************************/

	void RigidComponent::SetTranslate(const Math::Vector3& position)
	{
		object->SetTranslate(Vector3ToPhysicsVector3(position));
	}
	const Math::Vector3 RigidComponent::GetTranslate() const
	{
		return PhysicsVector3ToVector3(object->GetTranslate());
	}
	void RigidComponent::SetRotation(const Math::Quaternion& Rotation)
	{
		object->SetRotation(QuaternionToPhysicsVector4(Rotation));
	}
	const Math::Quaternion RigidComponent::GetRotation() const
	{
		return PhysicsVector4ToQuaternion(object->GetRotation());
	}
	void RigidComponent::SetTransform(const Transform& transform)
	{
		object->SetTransform(TransformToPhysicsTransform(transform));
	}
	const Transform RigidComponent::GetTransform() const
	{
		return PhysicsTransformToTransform(object->GetTransform());
	}



	/********************************
				   Shape
	*********************************/
	void RigidComponent::SetFlag(Physics::CollisionType flag, bool value)
	{
		shape->SetFlag(static_cast<PhysicsEngineAPI::Utils::DataStructure::CollisionType>(flag), value);
	}
	void RigidComponent::SetLocalTranslate(const Math::Vector3& LocalTranslate)
	{
		shape->SetLocalTranslate(Vector3ToPhysicsVector3(LocalTranslate));
	}
	const Math::Vector3 RigidComponent::GetLocalTranslate() const
	{
		return PhysicsVector3ToVector3(shape->GetLocalTranslate());
	}
	void RigidComponent::SetLocalRotation(const Math::Quaternion& LocalRotation)
	{
		shape->SetLocalRotation(QuaternionToPhysicsVector4(LocalRotation));
	}
	const Math::Quaternion RigidComponent::GetLocalRotation() const
	{
		return PhysicsVector4ToQuaternion(shape->GetLocalRotation());
	}
	void RigidComponent::SetLocalTransform(const Transform& LocalTransform)
	{
		shape->SetLocalTransform(TransformToPhysicsTransform(LocalTransform));
	}
	const Transform RigidComponent::GetLocalTransform() const
	{
		return PhysicsTransformToTransform(shape->GetLocalTransform());
	}
	void RigidComponent::SetScale(const Math::Vector3& Scale)
	{
		shape->SetScale(Vector3ToPhysicsVector3(Scale));
	}
	const Math::Vector3 RigidComponent::GetScale() const
	{
		return PhysicsVector3ToVector3(shape->GetScale());
	}



	/********************************
				Geometry
	*********************************/
	void RigidComponent::SetType(Physics::GeometryShape type)
	{
		geometry->SetType(static_cast<PhysicsEngineAPI::Utils::DataStructure::GeometryShape>(type));
	}
	Physics::GeometryShape RigidComponent::GetType()
	{
		return static_cast<Physics::GeometryShape>(geometry->GetType());
	}



	/********************************
				Material
	*********************************/


	/********************************
			Engine Life Cycle
	*********************************/
	void RigidComponent::Initialize()
	{
		object->SetUserData(collision);
		if(nullptr != shape) shape->SetUserData(collision);
	}
	void RigidComponent::Update(float deltaTime) const
	{
		// TODO Transform Update(Respone)
		// TODO 로직 후 적용
		// TODO Transform Update(Request)
		// TODO
		// TODO
		// TODO
		// TODO
	}

	void RigidComponent::FixedUpdate() const
	{
		collision->FixedUpdate();
	}

	void RigidComponent::Finalize()
	{
		constexpr Utility::SafeRelease releaser;

		releaser(&object);
		releaser(&shape);
		releaser(&geometry);
		releaser(&material);
		releaser(&collision);
	}

	void* RigidComponent::GetOwner()
	{
		return owner->GetOwner();
	}

	void RigidComponent::BindCollision(const Physics::CallBackTrigger& callback, Physics::TriggerType type)
	{
		collision->BindCollision(callback, type);
	}
	void RigidComponent::BindCollision(const Physics::CallBackContact& callback, Physics::ContactType type)
	{
		collision->BindCollision(callback, type);
	}
}
