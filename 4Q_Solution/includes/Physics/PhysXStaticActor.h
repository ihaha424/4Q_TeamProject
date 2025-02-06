#pragma once
#include "IStaticObject.h"
#include "PhysXActorFunction.h"

namespace PhysicsEngineAPI
{
	class PhysXStaticActor
		: public IStaticObject
	{
	public:
		explicit	PhysXStaticActor(physx::PxRigidStatic* actor);
		virtual		~PhysXStaticActor();
		void Release() override;
	public:
		bool AttachShape(IShape* shape) override;
		bool DetachShape(IShape* shape) override;

		void	SetTranslate(const Utils::Math::Vector3& position)		override;
			Utils::Math::Vector3 GetTranslate() const				override;
		void	SetRotation(const Utils::Math::Vector4& Rotation)		override;
			Utils::Math::Vector4 GetRotation() const				override;
		void	SetTransform(const Utils::Math::Transform& transform)	override;
			Utils::Math::Transform GetTransform() const				override;

		void SetName(const char* name)	override;
		const char* GetName() const		override;

		void SetUserData(ICollision* userData)	override;
		const ICollision* GetUserData() const	override;
		void ClearUserData()					override;

		void* GetPhysicsObject() override;

		physx::PxRigidStatic* operator->() { return actor; }

	private:
		physx::PxRigidStatic* actor;
		PhysXStaticActorFunction function;

		friend class PhysXSystem;
	};
}
