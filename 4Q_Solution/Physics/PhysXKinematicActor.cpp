#include "pch.h"
#include "PhysXKinematicActor.h"

namespace Physics
{
	PhysXKinematicActor::PhysXKinematicActor(physx::PxRigidDynamic* actor)
		: PhysXDynamicActor(actor)
	{}

	PhysXKinematicActor::~PhysXKinematicActor()
	{}
}