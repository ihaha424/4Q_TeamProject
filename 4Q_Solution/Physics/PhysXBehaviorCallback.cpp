#include "pch.h"
#include "PhysXBehaviorCallback.h"
#include "IController.h"

namespace PhysicsEngineAPI
{
	physx::PxControllerBehaviorFlags PhysXBehaviorCallback::getBehaviorFlags(const physx::PxShape& shape, const physx::PxActor& actor)
	{
		return physx::PxControllerBehaviorFlags();
	}
	physx::PxControllerBehaviorFlags PhysXBehaviorCallback::getBehaviorFlags(const physx::PxController& controller)
	{
		return physx::PxControllerBehaviorFlags();
	}
	physx::PxControllerBehaviorFlags PhysXBehaviorCallback::getBehaviorFlags(const physx::PxObstacle& obstacle)
	{
		return physx::PxControllerBehaviorFlags();
	}
	void PhysXBehaviorCallback::SetUserData(ICollision* _userData)
	{
		userData = _userData;
	}
}
