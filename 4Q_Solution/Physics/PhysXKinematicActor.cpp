#include "pch.h"
#include "PhysXKinematicActor.h"

namespace PhysicsEngineAPI
{
	PhysXKinematicActor::PhysXKinematicActor(physx::PxRigidDynamic* actor)
		: PhysXDynamicActor(actor)
	{}

	PhysXKinematicActor::~PhysXKinematicActor()
	{}
}