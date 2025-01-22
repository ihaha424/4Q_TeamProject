#pragma once
#include "PhysXActor.h"
#include "IDynamicObject.h"

namespace PhysicsEngineAPI
{
	class PhysXDynamicActor
		: public PhysXActor
		, virtual public IDynamicObject
	{
	public:
		explicit	PhysXDynamicActor(physx::PxRigidDynamic* actor);
		virtual		~PhysXDynamicActor();

		void	SetVelocity(const Utils::Math::Vector3& velocity)				override;
		const	Utils::Math::Vector3 GetVelocity() const						override;

		void	SetLinearVelocity(const Utils::Math::Vector3& velocity)			override;
		const	Utils::Math::Vector3& GetLinearVelocity() const					override;

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


	};
}
