#pragma once
#include "PhysXUtils.h"

namespace PhysicsEngineAPI
{
	class IController;
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

		void SetUserData(IController* userData);
	private:
		IController* userData;
	};
}
