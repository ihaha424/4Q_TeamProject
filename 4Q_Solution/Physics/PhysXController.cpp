#include "pch.h"
#include "PhysXController.h"

namespace PhysicsEngineAPI
{
	PhysXController::PhysXController()
		: gravity{ 0,0,0 }
		, flags{ 0 }
		, controller{ nullptr }
	{
	}
	void PhysXController::SetName(const char* Name)
	{
		controller->getActor()->setName(Name);
	}
	const char* PhysXController::GetName() const
	{
		return controller->getActor()->getName();
	}
	void PhysXController::SetUserData(ICollision* UserData)
	{
		controller->setUserData(UserData);
		controller->getActor()->userData = UserData;
		hitReportCallback->SetUserData(UserData);
		behaviorCallback->SetUserData(UserData);
	}
	const ICollision* PhysXController::GetUserData() const
	{
		return static_cast<ICollision*>(controller->getUserData());
	}
	void PhysXController::ClearUserData()
	{
		controller->setUserData(nullptr);
	}
	void PhysXController::Release()
	{
		SAFE_RELEASE(controller);
	}

	/***********************************
				Controller
	************************************/
	unsigned short PhysXController::Move(const Utils::Math::Vector3 _displacement, float minDistance, float deltaTime)
	{
		physx::PxVec3 displacement = Vector3ToPxVec3(_displacement);
		const physx::PxControllerFilters filters{};
		const physx::PxObstacleContext* obstacles = NULL;
		//controller->invalidateCache();
		flags = controller->move(displacement, minDistance, deltaTime, filters);
		return flags;
	}
	void PhysXController::SetGravity(const Utils::Math::Vector3& _gravity)
	{
		gravity = Vector3ToPxVec3(_gravity);
	}
	const Utils::Math::Vector3& PhysXController::GetGravity() const
	{
		return PxVec3ToVector3(gravity);
	}
	void PhysXController::SetPosition(const Utils::Math::Vector3& position)
	{
		controller->setPosition(Vector3ToPxExtendedVec3(position));
	}
	const Utils::Math::Vector3 PhysXController::GetPosition() const
	{
		return PxExtendedVec3ToVector3(controller->getPosition());
	}
	void PhysXController::SetBottomPosition(const Utils::Math::Vector3& position)
	{
		controller->setFootPosition(Vector3ToPxExtendedVec3(position));
	}
	const Utils::Math::Vector3& PhysXController::GetBottomPosition() const
	{
		return PxExtendedVec3ToVector3(controller->getFootPosition());
	}
	void PhysXController::SetStepOffset(float offset)
	{
		controller->setStepOffset(offset);
	}
	float PhysXController::GetStepOffset() const
	{
		return controller->getStepOffset();
	}
	void PhysXController::SetNonWalkSlide(const Utils::DataStructure::ControllerSlope mode)
	{
		physx::PxControllerNonWalkableMode::Enum flag = static_cast<physx::PxControllerNonWalkableMode::Enum>(mode);
		controller->setNonWalkableMode(flag);
	}
	Utils::DataStructure::ControllerSlope PhysXController::GetNonWalkSlide() const
	{
		Utils::DataStructure::ControllerSlope flag = static_cast<Utils::DataStructure::ControllerSlope>(controller->getNonWalkableMode());
		return flag;
	}
	void PhysXController::SetContactOffset(float offset)
	{
		controller->setContactOffset(offset);
	}
	float PhysXController::GetContactOffset() const
	{
		return controller->getContactOffset();
	}
	void PhysXController::SetUpDirection(const Utils::Math::Vector3& direction)
	{
		controller->setUpDirection(Vector3ToPxVec3(direction));
	}
	const Utils::Math::Vector3& PhysXController::GetUpdirection() const
	{
		return PxVec3ToVector3(controller->getUpDirection());
	}
	void PhysXController::SetSlopeLimit(float limit)
	{
		controller->setSlopeLimit(limit);
	}
	float PhysXController::GetSlopeLimit() const
	{
		return controller->getSlopeLimit();
	}
	void PhysXController::InvalidateCache()
	{
		controller->invalidateCache();
	}
	void PhysXController::GetState(Utils::DataStructure::ControllerState& _state) const
	{
		physx::PxControllerState state;
		controller->getState(state);
		_state.controllerCollisionFlag = state.collisionFlags;
		_state.position = PxVec3ToVector3(state.deltaXP);
		_state.isStandingCCT = state.standOnAnotherCCT;
		_state.isStandingObstacle = state.standOnObstacle;
		_state.isMovingUp = state.isMovingUp;
	}






	/***********************************
			Capsule Controller
	************************************/
	void PhysXController::SetRadius(float offset)
	{
		controller->setRadius(offset);
	}
	float PhysXController::GetRadius() const
	{
		return controller->getRadius();
	}
	void PhysXController::SetHeight(float offset)
	{
		controller->setHeight(offset);
	}
	float PhysXController::GetHeight() const
	{
		return controller->getHeight();
	}
	void PhysXController::SetClimbingMode(const Utils::DataStructure::CapsuleClimbingMode mode)
	{
		physx::PxCapsuleClimbingMode::Enum flag = static_cast<physx::PxCapsuleClimbingMode::Enum>(mode);
		controller->setClimbingMode(flag);
	}
	Utils::DataStructure::CapsuleClimbingMode PhysXController::GetClimbingMode() const
	{
		Utils::DataStructure::CapsuleClimbingMode flag = static_cast<Utils::DataStructure::CapsuleClimbingMode>(controller->getNonWalkableMode());
		return flag;
	}
	void PhysXController::CollisionUpdate()
	{
		hitReportCallback->Update();
	}
}