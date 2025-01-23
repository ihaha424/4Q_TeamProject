#pragma once
#include "PhysicsDynamicObject.h"

namespace Engine::Physics
{
	struct IKinematicObject
		: DynamicObject
	{
	};

	struct KinematicObject
		: IKinematicObject
	{
	};
}

