#pragma once
#include "PHICollision.h"

namespace Engine::PHI
{
	class Controller final
		: public Physics::Controller
	{
	public:
		Controller();

		/***********************************
					Controller
		************************************/
		void SetName(const char* Name) override;
		const char* GetName() const override;

		void ClearUserData() override;

		unsigned short Move(Engine::Math::Vector3 displacement, float minDistance, float deltaTime) override;
		
		void SetGravity(const Engine::Math::Vector3& gravity) override;
		const Engine::Math::Vector3& GetGravity() const override;

		void SetPosition(const Engine::Math::Vector3& position) override;
		const Engine::Math::Vector3& GetPosition() const override;

		void SetBottomPosition(const Engine::Math::Vector3& position) override;
		const Engine::Math::Vector3& GetBottomPosition() const override;

		void SetStepOffset(float offset) override;
		float GetStepOffset() const override;

		void SetNonWalkSlide(const Engine::Physics::ControllerSlope mode) override;
		Engine::Physics::ControllerSlope GetNonWalkSlide() const override;

		void SetContactOffset(float offset) override;
		float GetContactOffset() const override;

		void SetUpDirection(const Engine::Math::Vector3& direction) override;
		const Engine::Math::Vector3& GetUpdirection() const override;

		void SetSlopeLimit(float limit) override;
		float GetSlopeLimit() const override;

		void InvalidateCache() override;

		void GetState(Engine::Physics::ControllerState& state) const override;
		

		/***********************************
				Capsule Controller
		************************************/
		void SetRadius(float offset) override;
		float GetRadius() const override;

		void SetHeight(float offset) override;
		float GetHeight() const override;

		void SetClimbingMode(const Engine::Physics::CapsuleClimbingMode mode) override;
		Engine::Physics::CapsuleClimbingMode GetClimbingMode() const override;


		/***********************************
					Engine
		************************************/
		void Initialize() override;
		void Update(float deltaTime) const override;
		void Finalize() override;
	private:
		PhysicsEngineAPI::IController* controller;
		Collision<Controller>* collision;
		unsigned short controllerCollisionFlag;

		friend class Manager;

		// Controller을(를) 통해 상속됨
		void FixedUpdate() const override;
	};
}

