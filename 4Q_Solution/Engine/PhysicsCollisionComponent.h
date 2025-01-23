#pragma once

#include "PhysicsComponent.h"

namespace Engine::Physics
{
	struct ICollisionComponent : Component
	{
		// Refer. Unity Collosion
		virtual void __CALLBACK__ OnTriggerEnter() = 0;
		virtual void __CALLBACK__ OnTrigger() = 0;
		virtual void __CALLBACK__ OnTriggerExit() = 0;
		virtual void __CALLBACK__ OnCollisionEnter() = 0;
		virtual void __CALLBACK__ OnCollision() = 0;
		virtual void __CALLBACK__ OnCollisionExit() = 0;

		// Refer. Unreal Collosion
		virtual void __CALLBACK__ OnHit() = 0;
		virtual void __CALLBACK__ OnOverlapBegin() = 0;
		virtual void __CALLBACK__ OnOverlapEnd() = 0;
	};

	struct CollisionComponent : ICollisionComponent
	{
		virtual void SetOwner() = 0;
	};
}