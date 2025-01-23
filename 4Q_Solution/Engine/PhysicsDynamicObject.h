#pragma once

#include "PhysicsObject.h"

namespace Engine::Physics
{
	struct IDynamicObject
		: virtual IObject
	{
		virtual void	SetVelocity(const Utils::Math::Vector3& velocity) = 0;
		virtual const	Utils::Math::Vector3 GetVelocity() const = 0;

		virtual void	SetLinearVelocity(const Utils::Math::Vector3& velocity) = 0;
		virtual const	Utils::Math::Vector3& GetLinearVelocity() const = 0;

		virtual void	SetMaxLinearVelocity(const float velocity) = 0;
		virtual const	float GetMaxLinearVelocity() const = 0;

		virtual void	SetAngularVelocity(const Utils::Math::Vector3& angularVelocity) = 0;
		virtual const	Utils::Math::Vector3 GetAngularVelocity() const = 0;

		virtual void	SetMaxAngularVelocity(const float velocity) = 0;
		virtual const	float GetMaxAngularVelocity() const = 0;

		virtual void	Wakeup() = 0;
		virtual bool	IsSleeping() = 0;
		virtual void	PutToSleep() = 0;
		virtual void	SetSleepThreshold() = 0;	// 잠자는 상태로 전환되기 위한 속도 임계값 설정
		virtual void	SetWakeCounter(float timer) = 0;
		virtual float	GetWakeCounter() = 0;

		// Force Related
		virtual void	AddForce(const Utils::Math::Vector3& force) = 0;
		virtual void	AddTorque(const Utils::Math::Vector3& force) = 0;
		virtual void	ClearForce() = 0;
		virtual void	ClearTorque() = 0;
	};

	struct DynamicObject
		: virtual IDynamicObject
	{
	};
}