#pragma once

#include "PhysicsObject.h"

namespace Engine::Physics
{
	struct IDynamicObject
		: IObject
	{
		void	SetVelocity(const Utils::Math::Vector3& velocity);
		const	Utils::Math::Vector3 GetVelocity() const;

		void	SetLinearVelocity(const Utils::Math::Vector3& velocity);
		const	Utils::Math::Vector3& GetLinearVelocity() const;

		void	SetMaxLinearVelocity(const float velocity);
		const	float GetMaxLinearVelocity() const;

		void	SetAngularVelocity(const Utils::Math::Vector3& angularVelocity);
		const	Utils::Math::Vector3 GetAngularVelocity() const;

		void	SetMaxAngularVelocity(const float velocity);
		const	float GetMaxAngularVelocity() const;

		void	Wakeup();
		bool	IsSleeping();
		void	PutToSleep();
		void	SetSleepThreshold();
		void	SetWakeCounter(float timer);
		float	GetWakeCounter();

		// Force Related
		void	AddForce(const Utils::Math::Vector3& force);
		void	AddTorque(const Utils::Math::Vector3& force);
		void	ClearForce();
		void	ClearTorque();
	};

	struct DynamicObject
		: virtual IDynamicObject
	{
	};
}