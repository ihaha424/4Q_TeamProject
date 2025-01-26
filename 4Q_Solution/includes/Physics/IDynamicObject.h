#pragma once
#include "IObject.h"

namespace PhysicsEngineAPI
{
	__INTERFACE__
	EXTERN_C class PHYSICS_API IDynamicObject
		: public IObject
	{
	public:
		virtual ~IDynamicObject() = default;


		// Transform 관련 함수
		/**
		 * @brief
		 */
		virtual void	SetVelocity(const Utils::Math::Vector3& velocity)	= 0;
		virtual const	Utils::Math::Vector3 GetVelocity() const			= 0;

		virtual void	SetLinearVelocity(const Utils::Math::Vector3& velocity) = 0;
		virtual const	Utils::Math::Vector3 GetLinearVelocity() const			= 0;

		virtual void	SetMaxLinearVelocity(const float velocity)	= 0;
		virtual const	float GetMaxLinearVelocity() const			= 0;

		virtual void	SetAngularVelocity(const Utils::Math::Vector3& angularVelocity)	= 0;
		virtual const	Utils::Math::Vector3 GetAngularVelocity() const					= 0;

		virtual void	SetMaxAngularVelocity(const float velocity)	= 0;
		virtual const	float GetMaxAngularVelocity() const			= 0;




		// Slepp & Wakeup Related
		/**
		* @brief 피직스는 기본적으로 알아서 최적화 되어서 움직임이나 힘이 없으면 잔다.
		이를 깨우는 함수
		*/
		virtual void	Wakeup()					= 0;
		virtual bool	IsSleeping()				= 0;
		virtual void	PutToSleep()				= 0;
		virtual void	SetSleepThreshold()			= 0;	// 잠자는 상태로 전환되기 위한 속도 임계값 설정
		virtual void	SetWakeCounter(float timer)	= 0;
		virtual float	GetWakeCounter()			= 0;
		 
		// Force Related
		virtual void	AddForce(const Utils::Math::Vector3& force)		= 0;
		virtual void	AddTorque(const Utils::Math::Vector3& force)	= 0;
		virtual void	ClearForce()	= 0;
		virtual void	ClearTorque()	= 0;
	};
}
