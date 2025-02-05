#pragma once

#include "IController.h"
#include "PhysXUtils.h"
#include "PhysXReportCallback.h"
#include "PhysXBehaviorCallback.h"

namespace PhysicsEngineAPI
{
	class PhysXController
		: public IController
	{
	public:
		PhysXController();
		void SetName(const char* Name) override;
		const char* GetName() const override;

		void SetUserData(ICollision* UserData) override;
		const ICollision* GetUserData() const override;
		void ClearUserData() override;

		void Release() override;

		void CollisionUpdate() override;

		/***********************************
					Controller
		************************************/
		// IDynamicObject* GetActor() const override;
		
		unsigned short Move(const Utils::Math::Vector3 displacement, float minDistance, float deltaTime) override;
		
		void SetGravity(const Utils::Math::Vector3& gravity) override;
		const Utils::Math::Vector3& GetGravity() const override;

		void SetPosition(const Utils::Math::Vector3& position) override;
		const Utils::Math::Vector3& GetPosition() const override;

		void SetBottomPosition(const Utils::Math::Vector3& position) override;
		const Utils::Math::Vector3& GetBottomPosition() const override;

		void SetStepOffset(float offset) override;
		float GetStepOffset() const override;

		void SetNonWalkSlide(const Utils::DataStructure::ControllerSlope mode) override;
		Utils::DataStructure::ControllerSlope GetNonWalkSlide() const override;

		void SetContactOffset(float offset) override;
		float GetContactOffset() const override;

		void SetUpDirection(const Utils::Math::Vector3& direction) override;
		const Utils::Math::Vector3& GetUpdirection() const override;

		void SetSlopeLimit(float limit) override;
		float GetSlopeLimit() const override;

		void InvalidateCache() override;

		void GetState(Utils::DataStructure::ControllerState& state) const override;

		/***********************************
				Capsule Controller
		************************************/
		void SetRadius(float offset) override;
		float GetRadius() const override;
		void SetHeight(float offset) override;
		float GetHeight() const override;
		void SetClimbingMode(const const Utils::DataStructure::CapsuleClimbingMode mode) override;
		Utils::DataStructure::CapsuleClimbingMode GetClimbingMode() const override;

	private:
		/***********************************
				Capsule Controller
		************************************/
		physx::PxCapsuleController* controller;
		PhysXReportCallback*	hitReportCallback;
		PhysXBehaviorCallback*	behaviorCallback;
		
		/***********************************
				Controller
		************************************/
		physx::PxVec3 gravity;
		physx::PxU8 flags;
		

		friend class PhysXSystem;
	};
}
