#pragma once
#include "IObject.h"
#include "PhysXUtils.h"
#include "PhysXScene.h"

namespace PhysicsEngineAPI
{
	class PhysXActor
		: virtual public IObject
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

		physx::PxRigidActor* operator->() { return actor; }

	protected:
		physx::PxRigidActor* actor;

		friend class PhysXScene;
		friend class PhysXSystem;

		// IObject을(를) 통해 상속됨
		void Test() override;
	};
}

