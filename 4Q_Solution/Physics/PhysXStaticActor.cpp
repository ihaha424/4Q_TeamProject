#include "pch.h"
#include "PhysXStaticActor.h"

namespace PhysicsEngineAPI
{
	PhysXStaticActor::PhysXStaticActor(physx::PxRigidStatic* actor)
		: PhysXActor(actor)
	{}
	PhysXStaticActor::~PhysXStaticActor()
	{}
}
