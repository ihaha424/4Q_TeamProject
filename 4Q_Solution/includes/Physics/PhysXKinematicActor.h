#pragma once
#include "PhysXDynamicActor.h"
#include "IKinematicObject.h"

namespace PhysicsEngineAPI
{
	class PhysXKinematicActor
		: public PhysXDynamicActor
		, virtual public IKinematicObject
	{
	public:
		explicit	PhysXKinematicActor(physx::PxRigidDynamic* actor);
		virtual		~PhysXKinematicActor();
	};
}
