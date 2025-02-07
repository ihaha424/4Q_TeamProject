#pragma once

namespace Engine::Physics
{
	// Client Interface
	struct IController : Component
	{
		virtual void SetName(const char* Name) = 0;
		virtual const char* GetName() const = 0;

		virtual void	ClearUserData() = 0;

		/***********************************
				Kinematic Move Setting
		************************************/
		virtual void AddForce(const Engine::Math::Vector3& force) = 0;
		virtual void AddVelocity(const Engine::Math::Vector3& velocity) = 0;
		virtual void SetVelocity(const Engine::Math::Vector3& velocity) = 0;
		virtual Engine::Math::Vector3 GetVelocity() = 0;
		virtual void ClearVelocity() = 0;
		virtual void SetMass(float mass) = 0;
		virtual float GetMass() = 0;


		/***********************************
					Controller
		************************************/

		virtual void Jump(float JumpForce) = 0;

		virtual void SetDirection(Engine::Math::Vector3 displacement) = 0;
		virtual  Engine::Math::Vector3 GetDirection() const = 0;

		virtual void SetMinDistancet(float minDistance) = 0;
		virtual float GetMinDistance() const = 0;

		virtual void SetMoveSpeed(float moveSpeed) = 0;
		virtual float GetMoveSpeed() const = 0;

		virtual void SetGravity(const Engine::Math::Vector3& gravity) = 0;
		virtual  Engine::Math::Vector3 GetGravity() const = 0;

		virtual void SetPosition(const Engine::Math::Vector3& position) = 0;
		virtual  Engine::Math::Vector3 GetPosition() const = 0;

		virtual void SetBottomPosition(const Engine::Math::Vector3& position) = 0;
		virtual  Engine::Math::Vector3 GetBottomPosition() const = 0;

		virtual void SetStepOffset(float offset) = 0;
		virtual float GetStepOffset() const = 0;

		virtual void SetNonWalkSlide(const Engine::Physics::ControllerSlope mode) = 0;
		virtual Engine::Physics::ControllerSlope GetNonWalkSlide() const = 0;

		virtual void SetContactOffset(float offset) = 0;
		virtual float GetContactOffset() const = 0;

		virtual void SetUpDirection(const Engine::Math::Vector3& direction) = 0;
		virtual  Engine::Math::Vector3 GetUpdirection() const = 0;

		virtual void SetSlopeLimit(float limit) = 0;
		virtual float GetSlopeLimit() const = 0;

		virtual void InvalidateCache() = 0;

		virtual void GetState(Engine::Physics::ControllerState& state) const = 0;
		virtual unsigned short GetCollisionFlag() = 0;

		/***********************************
				Capsule Controller
		************************************/
		virtual void SetRadius(float offset) = 0;
		virtual float GetRadius() const = 0;

		virtual void SetHeight(float offset) = 0;
		virtual float GetHeight() const = 0;

		virtual void SetClimbingMode(const Engine::Physics::CapsuleClimbingMode mode) = 0;
		virtual Engine::Physics::CapsuleClimbingMode GetClimbingMode() const = 0;

		/********************************
					Collision
		*********************************/
		virtual void BindCollision(const CallBackTrigger& callback, TriggerType type) = 0;
		virtual void BindCollision(const CallBackContact& callback, ContactType type) = 0;
	};

	// Engine Interface
	struct Controller : IController
	{
		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual void FixedUpdate() = 0;
		virtual void Finalize() = 0;
	};
}
