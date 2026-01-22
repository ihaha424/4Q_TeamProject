#pragma once

namespace Engine::Physics
{
	struct IRigidDynamicComponent : IRigidComponent
	{
		/********************************
				Transform Associate
		*********************************/
		virtual void	SetVelocity(const Engine::Math::Vector3& velocity) = 0;
		virtual 	Engine::Math::Vector3 GetVelocity() const = 0;

		virtual void	SetLinearVelocity(const Engine::Math::Vector3& velocity) = 0;
		virtual 	Engine::Math::Vector3 GetLinearVelocity() const = 0;

		virtual void	SetMaxLinearVelocity(const float velocity) = 0;
		virtual 	float GetMaxLinearVelocity() const = 0;

		virtual void	SetAngularVelocity(const Engine::Math::Vector3& angularVelocity) = 0;
		virtual 	Engine::Math::Vector3 GetAngularVelocity() const = 0;

		virtual void	SetMaxAngularVelocity(const float velocity) = 0;
		virtual 	float GetMaxAngularVelocity() const = 0;


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

	struct RigidDynamicComponent : IRigidDynamicComponent
	{
		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) const = 0;
		virtual void FixedUpdate() const = 0;
		virtual void Finalize() = 0;

		/********************************
					   Rigid
		*********************************/
		//virtual bool	AttachShape(Shape* shape) = 0;
		//virtual bool	DetachShape(Shape* shape) = 0;


		///********************************
		//			Collision
		//*********************************/
		//virtual void SetUserData(ICollision* UserData) = 0;
		//virtual const ICollision* GetUserData() const = 0;

		/********************************
					Shape
		*********************************/


		/********************************
					Geometry
		*********************************/
		virtual void SetType(GeometryShape type) = 0;


		/********************************
					Material
		*********************************/
	};
}
