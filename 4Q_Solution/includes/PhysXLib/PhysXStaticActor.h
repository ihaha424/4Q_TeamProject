#pragma once
#include "PhysXActor.h"
#include "IStaticObject.h"

namespace Physics
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
