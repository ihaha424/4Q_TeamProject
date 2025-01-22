#pragma once
#include "PhysXActor.h"
#include "IStaticObject.h"

namespace PhysicsEngineAPI
{
	class PhysXStaticActor
		: public PhysXActor
		, virtual public IStaticObject
	{
	public:
		explicit	PhysXStaticActor(physx::PxRigidStatic* actor);
		virtual		~PhysXStaticActor();

	};
}
