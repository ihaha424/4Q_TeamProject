#pragma once
#include "IObject.h"
#include "PhysXUtils.h"
#include "PhysXActorFunction.h"

namespace PhysicsEngineAPI
{
	class PhysXActor
		: public IObject
	{
	public:
		explicit	PhysXActor(physx::PxRigidActor* actor);
		virtual		~PhysXActor();

		bool AttachShape(IShape* shape) override;
		bool DetachShape(IShape* shape) override;

		void	SetTranslate(const Utils::Math::Vector3& position)		override;
		const	Utils::Math::Vector3 GetTranslate() const				override;
		void	SetRotation(const Utils::Math::Vector4& Rotation)		override;
		const	Utils::Math::Vector4 GetRotation() const				override;
		void	SetTransform(const Utils::Math::Transform& transform)	override;
		const	Utils::Math::Transform GetTransform() const				override;

		void SetName(const char* name)	override;
		const char* GetName() const		override;

		void SetUserData(ICollision* userData)	override;
		const ICollision* GetUserData() const	override;
		void ClearUserData()					override;

		void* GetPhysicsObject() override;

		physx::PxRigidActor* operator->() { return actor; }

	public:
		void Release() override;

	protected:
		physx::PxRigidActor* actor;
		PhysXActorFunction function;

		friend class PhysXSystem;
	};
}

