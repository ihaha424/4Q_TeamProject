#pragma once
#include "IDynamicObject.h"
#include "PhysXActorFunction.h"

namespace PhysicsEngineAPI
{
	class PhysXDynamicActor
		: public IDynamicObject
	{
	public:
		explicit	PhysXDynamicActor(physx::PxRigidDynamic* actor);
		virtual		~PhysXDynamicActor();
		void		Release() override;
	public:
		void	SetVelocity(const Utils::Math::Vector3& velocity)				override;
		const	Utils::Math::Vector3 GetVelocity() const						override;

		void	SetLinearVelocity(const Utils::Math::Vector3& velocity)			override;
		const	Utils::Math::Vector3 GetLinearVelocity() const					override;

		void	SetMaxLinearVelocity(const float velocity)		override;
		const	float GetMaxLinearVelocity() const				override;

		void	SetAngularVelocity(const Utils::Math::Vector3& angularVelocity)	override;
		const	Utils::Math::Vector3 GetAngularVelocity() const					override;

		void	SetMaxAngularVelocity(const float velocity)		override;
		const	float GetMaxAngularVelocity() const				override;


		//TODO: 고쳐야함
		void	Wakeup()					override;
		bool	IsSleeping()				override;
		void	PutToSleep()				override;
		void	SetSleepThreshold()			override;
		void	SetWakeCounter(float timer)	override;
		float	GetWakeCounter()			override;

		void	AddForce(const Utils::Math::Vector3& force)		override;
		void	AddTorque(const Utils::Math::Vector3& force)	override;
		void	ClearForce()									override;
		void	ClearTorque()									override;

	//IObject
	public:
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

		physx::PxRigidDynamic* operator->() { return actor; }
	private:
		physx::PxRigidDynamic* actor;
		PhysXDynamicActorFunction function;

		friend class PhysXSystem;
	};
}
