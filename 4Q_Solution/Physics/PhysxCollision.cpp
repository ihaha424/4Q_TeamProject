#include "pch.h"
#include "PhysxCollision.h"

using namespace physx;
namespace PhysicsEngineAPI
{
	void PhysxCollisionEvent::onContact(const PxContactPairHeader& pairHeader, const PxContactPair* pairs, PxU32 nbPairs)
	{
		if (pairHeader.flags & PxContactPairHeaderFlag::eREMOVED_ACTOR_0) 
		{
			printf("Actor 0 was removed during the collision.\n");
			return;
		}
		if (pairHeader.flags & PxContactPairHeaderFlag::eREMOVED_ACTOR_1) 
		{
			printf("Actor 1 was removed during the collision.\n");
			return;
		}



		for (PxU32 i = 0; i < nbPairs; i++) {
			const PxContactPair& pair = pairs[i];

			// Shape
			if (pair.events & PxPairFlag::eNOTIFY_TOUCH_FOUND) 
			{
				//OnCollisionEnter();
				//OnHit();
			}

			if (pair.events & PxPairFlag::eNOTIFY_TOUCH_PERSISTS) 
			{
				//OnCollision();
			}

			if (pair.events & PxPairFlag::eNOTIFY_TOUCH_LOST) 
			{
				//OnCollisionExit();
			}
		}
		ICollision* actor1 = static_cast<ICollision*>(pairHeader.actors[0]->userData);
		ICollision* actor2 = static_cast<ICollision*>(pairHeader.actors[1]->userData);
		if (actor1) 
			actor1->OnHit();
		if (actor2) 
			actor2->OnHit();
	}

	void PhysxCollisionEvent::onTrigger(PxTriggerPair* pairs, PxU32 count)
	{
		for (PxU32 i = 0; i < count; i++) {
			const PxTriggerPair& pair = pairs[i];

			if (pair.status & PxPairFlag::eNOTIFY_TOUCH_FOUND) 
			{
				
				pair.otherShape;
				pair.triggerShape;
				pair.otherActor;
				pair.triggerActor;
				//OnTriggerEnter();
				//OnOverlapBegin();
			}

			if (pair.status & PxPairFlag::eNOTIFY_TOUCH_PERSISTS) 
			{
				//OnTrigger();
			}

			if (pair.status & PxPairFlag::eNOTIFY_TOUCH_LOST) 
			{
				//OnTriggerExit();
				//OnOverlapEnd();
			}
		}
	}

	void PhysxCollisionEvent::onWake(PxActor** actors, PxU32 count)
	{
	}

	void PhysxCollisionEvent::onSleep(PxActor** actors, PxU32 count)
	{
	}

	void PhysxCollisionEvent::onConstraintBreak(PxConstraintInfo* constraints, PxU32 count)
	{
	}

	void PhysxCollisionEvent::onAdvance(const PxRigidBody* const* bodyBuffer, const PxTransform* poseBuffer, const PxU32 count)
	{
	}
}