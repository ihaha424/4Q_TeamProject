#pragma once
#include "PhysicsDynamicObject.h"

namespace Engine::Physics
{
	struct IKinematicObject
		: virtual DynamicObject
	{
	};

	struct KinematicObject
		: virtual IKinematicObject
	{
	};
}

