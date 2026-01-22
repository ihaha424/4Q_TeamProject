#pragma once
#include "PhysXUtils.h"

namespace PhysicsEngineAPI
{
	class ICollision;
}

namespace PhysicsEngineAPI
{
	class PhysXBehaviorCallback
		: public physx::PxControllerBehaviorCallback
	{
	public:
		// PxControllerBehaviorCallback을(를) 통해 상속됨
		physx::PxControllerBehaviorFlags getBehaviorFlags(const physx::PxShape& shape, const physx::PxActor& actor) override;
		physx::PxControllerBehaviorFlags getBehaviorFlags(const physx::PxController& controller) override;
		physx::PxControllerBehaviorFlags getBehaviorFlags(const physx::PxObstacle& obstacle) override;
	
		void SetUserData(ICollision* userData);
	private:
		ICollision* userData;
	};
}
