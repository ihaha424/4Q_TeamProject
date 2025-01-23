#pragma once

namespace PhysicsEngineAPI
{
	class IShape;
	class ICollision;
}

namespace PhysicsEngineAPI
{
	struct  PhysXActorFunction
	{
		bool AttachShape(IShape* shape, physx::PxRigidActor* actor);
		bool DetachShape(IShape* shape, physx::PxRigidActor* actor);

		void	SetTranslate(const Utils::Math::Vector3& position, physx::PxRigidActor* actor);
		const	Utils::Math::Vector3 GetTranslate(physx::PxRigidActor* actor) const;
		void	SetRotation(const Utils::Math::Vector4& Rotation, physx::PxRigidActor* actor);
		const	Utils::Math::Vector4 GetRotation(physx::PxRigidActor* actor) const;
		void	SetTransform(const Utils::Math::Transform& transform, physx::PxRigidActor* actor);
		const	Utils::Math::Transform GetTransform(physx::PxRigidActor* actor) const;

		void SetName(const char* name, physx::PxRigidActor* actor);
		const char* GetName(physx::PxRigidActor* actor) const;

		void SetUserData(ICollision* userData, physx::PxRigidActor* actor);
		const ICollision* GetUserData(physx::PxRigidActor* actor) const;
		void ClearUserData(physx::PxRigidActor* actor);

		void Release(physx::PxRigidActor* actor);
	};

	struct  PhysXStaticActorFunction : PhysXActorFunction
	{

	};

	struct  PhysXDynamicActorFunction : PhysXActorFunction
	{
		void	SetVelocity(const Utils::Math::Vector3& velocity, physx::PxRigidDynamic* actor);
		const	Utils::Math::Vector3 GetVelocity(physx::PxRigidDynamic* actor) const;

		void	SetLinearVelocity(const Utils::Math::Vector3& velocity, physx::PxRigidDynamic* actor);
		const	Utils::Math::Vector3& GetLinearVelocity(physx::PxRigidDynamic* actor) const;

		void	SetMaxLinearVelocity(const float velocity, physx::PxRigidDynamic* actor);
		const	float GetMaxLinearVelocity(physx::PxRigidDynamic* actor) const;

		void	SetAngularVelocity(const Utils::Math::Vector3& angularVelocity, physx::PxRigidDynamic* actor);
		const	Utils::Math::Vector3 GetAngularVelocity(physx::PxRigidDynamic* actor) const;

		void	SetMaxAngularVelocity(const float velocity, physx::PxRigidDynamic* actor);
		const	float GetMaxAngularVelocity(physx::PxRigidDynamic* actor) const;

		void	Wakeup(physx::PxRigidDynamic* actor);
		bool	IsSleeping(physx::PxRigidDynamic* actor);
		void	PutToSleep(physx::PxRigidDynamic* actor);
		void	SetSleepThreshold(physx::PxRigidDynamic* actor);
		void	SetWakeCounter(float timer, physx::PxRigidDynamic* actor);
		float	GetWakeCounter(physx::PxRigidDynamic* actor);

		void	AddForce(const Utils::Math::Vector3& force, physx::PxRigidDynamic* actor);
		void	AddTorque(const Utils::Math::Vector3& force, physx::PxRigidDynamic* actor);
		void	ClearForce(physx::PxRigidDynamic* actor);
		void	ClearTorque(physx::PxRigidDynamic* actor);
	};

	struct  PhysXKinematicActorFunction : PhysXDynamicActorFunction
	{

	};
};

