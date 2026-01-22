#pragma once
#include "PhysXUtils.h"

namespace PhysicsEngineAPI
{
	class ICollision;
}

namespace PhysicsEngineAPI
{
	class PhysXReportCallback
		: public physx::PxUserControllerHitReport
	{
	public:
		// PxUserControllerHitReport을(를) 통해 상속됨
		void onShapeHit(const physx::PxControllerShapeHit& hit) override;
		void onControllerHit(const physx::PxControllersHit& hit) override;
		void onObstacleHit(const physx::PxControllerObstacleHit& hit) override;

		void Update();
		void SetUserData(ICollision* userData);
	private:
		ICollision* userData;
		
		std::map<void*, bool> collitionMap;
		friend class PhysxController;
	};
}
