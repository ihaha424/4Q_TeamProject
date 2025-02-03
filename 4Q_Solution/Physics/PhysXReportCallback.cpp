#include "pch.h"
#include "PhysXReportCallback.h"
#include "IController.h"

namespace PhysicsEngineAPI
{
	void PhysXReportCallback::onShapeHit(const physx::PxControllerShapeHit& hit)
	{
	}
	void PhysXReportCallback::onControllerHit(const physx::PxControllersHit& hit)
	{

	}
	void PhysXReportCallback::onObstacleHit(const physx::PxControllerObstacleHit& hit)
	{
	}
	void PhysXReportCallback::SetUserData(IController* _userData)
	{
		userData = _userData;
	}
}
