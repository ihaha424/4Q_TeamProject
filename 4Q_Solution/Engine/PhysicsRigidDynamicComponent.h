#pragma once

namespace Engine::Physics
{
	struct IRigidDynamicComponent
	{
		/********************************
				Transform Associate
		*********************************/
		virtual void	SetVelocity(const Engine::Math::Vector3& velocity) = 0;
		virtual const	Engine::Math::Vector3 GetVelocity() const = 0;

		virtual void	SetLinearVelocity(const Engine::Math::Vector3& velocity) = 0;
		virtual const	Engine::Math::Vector3 GetLinearVelocity() const = 0;

		virtual void	SetMaxLinearVelocity(const float velocity) = 0;
		virtual const	float GetMaxLinearVelocity() const = 0;

		virtual void	SetAngularVelocity(const Engine::Math::Vector3& angularVelocity) = 0;
		virtual const	Engine::Math::Vector3 GetAngularVelocity() const = 0;

		virtual void	SetMaxAngularVelocity(const float velocity) = 0;
		virtual const	float GetMaxAngularVelocity() const = 0;


		/********************************
				Force Associate
		*********************************/
		virtual void	AddForce(const Engine::Math::Vector3& force) = 0;
		virtual void	AddTorque(const Engine::Math::Vector3& force) = 0;
		virtual void	ClearForce() = 0;
		virtual void	ClearTorque() = 0;


		/********************************
				State Associate
		*********************************/
		virtual void	Wakeup() = 0;
		virtual bool	IsSleeping() = 0;
		virtual void	PutToSleep() = 0;
		virtual void	SetSleepThreshold() = 0;
		virtual void	SetWakeCounter(float timer) = 0;
		virtual float	GetWakeCounter() = 0;
	};

	struct RigidDynamicComponent : IRigidDynamicComponent, RigidComponent
	{
		
	};
}
