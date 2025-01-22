#include "pch.h"
#include "PhysXStaticActor.h"

namespace Physics
{
	PhysXStaticActor::PhysXStaticActor(physx::PxRigidStatic* actor)
		: PhysXActor(actor)
	{}
	PhysXStaticActor::~PhysXStaticActor()
	{}
}
