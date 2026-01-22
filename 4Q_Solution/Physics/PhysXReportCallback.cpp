#include "pch.h"
#include "PhysXReportCallback.h"
#include "IController.h"
#include "ICollision.h"

using namespace physx;
namespace PhysicsEngineAPI
{
	void PhysXReportCallback::onShapeHit(const physx::PxControllerShapeHit& hit)
	{
        Utils::DataStructure::TriggerEvent triggerEvent{};
        ICollision* actor1 = static_cast<ICollision*>(userData);
        ICollision* actor2 = static_cast<ICollision*>(hit.actor->userData);

		if (collitionMap.find(actor2) == collitionMap.end())
		{
			if (actor1 && actor2)
			{
				collitionMap[actor2] = true;
				triggerEvent.myCollision = actor1;
				triggerEvent.otherCollision = actor2;
				actor1->OnOverlapBegin(triggerEvent);
				triggerEvent.myCollision = actor2;
				triggerEvent.otherCollision = actor1;
				actor2->OnOverlapBegin(triggerEvent);
			}
		}
	}
	void PhysXReportCallback::onControllerHit(const physx::PxControllersHit& hit)
	{

	}
	void PhysXReportCallback::onObstacleHit(const physx::PxControllerObstacleHit& hit)
	{
	}
	void PhysXReportCallback::Update()
	{
		for (auto it = collitionMap.begin(); it != collitionMap.end(); )
		{
			if (it->second == true)
			{
				// OnTrigger

				it->second = false;
				++it;
			}
			else
			{
				Utils::DataStructure::TriggerEvent triggerEvent{};
				ICollision* actor1 = static_cast<ICollision*>(userData);
				ICollision* actor2 = static_cast<ICollision*>(it->first);

				triggerEvent.myCollision = actor1;
				triggerEvent.otherCollision = actor2;
				actor1->OnOverlapEnd(triggerEvent);

				triggerEvent.myCollision = actor2;
				triggerEvent.otherCollision = actor1;
				actor2->OnOverlapEnd(triggerEvent);

				it = collitionMap.erase(it);
			}
		}
	}
	void PhysXReportCallback::SetUserData(ICollision* _userData)
	{
		userData = _userData;
	}
}
