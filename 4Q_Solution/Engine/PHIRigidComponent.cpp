#include "pch.h"
#include "PHIRigidComponent.h"

namespace Engine::PHI
{
	void RigidComponent::SetName(const char* Name)
	{
	}
	const char* RigidComponent::GetName() const
	{
		return nullptr;
	}
	void RigidComponent::SetTranslate(const Engine::Math::Vector3& position)
	{
	}
	const Engine::Math::Vector3 RigidComponent::GetTranslate() const
	{
		return Engine::Math::Vector3();
	}
	void RigidComponent::SetRotation(const Engine::Math::Vector4& Rotation)
	{
	}
	const Engine::Math::Vector4 RigidComponent::GetRotation() const
	{
		return Engine::Math::Vector4();
	}
	void RigidComponent::SetTransform(const Transform& transform)
	{
	}
	const Transform RigidComponent::GetTransform() const
	{
		return Transform();
	}
	void RigidComponent::SetFlag(CollisionType flag, bool value)
	{
	}
	void RigidComponent::SetLocalTranslate(const Engine::Math::Vector3& LocalTranslate)
	{
	}
	const Engine::Math::Vector3 RigidComponent::GetLocalTranslate() const
	{
		return Engine::Math::Vector3();
	}
	void RigidComponent::SetLocalRotation(const Engine::Math::Vector4& LocalRotation)
	{
	}
	const Engine::Math::Vector4 RigidComponent::GetLocalRotation() const
	{
		return Engine::Math::Vector4();
	}
	void RigidComponent::SetLocalTransform(const Engine::Transform& LocalTransform)
	{
	}
	const Engine::Transform RigidComponent::GetLocalTransform() const
	{
		return Engine::Transform();
	}
	void RigidComponent::SetScale(const Engine::Math::Vector3& Scale)
	{
	}
	const Engine::Math::Vector3 RigidComponent::GetScale() const
	{
		return Engine::Math::Vector3();
	}
	GeometryShape RigidComponent::SetType(GeometryShape type)
	{
		return GeometryShape();
	}
	void RigidComponent::GetType(GeometryShape type)
	{
	}
	void RigidComponent::Initialize()
	{
	}
	void RigidComponent::Update(float deltaTime) const
	{
	}
	void RigidComponent::Finalize()
	{
	}
	bool RigidComponent::AttachShape(Shape* shape)
	{
		return false;
	}
	bool RigidComponent::DetachShape(Shape* shape)
	{
		return false;
	}
}
