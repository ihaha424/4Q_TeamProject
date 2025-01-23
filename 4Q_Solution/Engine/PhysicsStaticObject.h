#pragma once
#include "PhysicsObject.h"

namespace Engine::Physics
{
	struct IStaticObject
		: virtual IObject
	{
	};

	struct StaticObject
		: virtual IStaticObject
	{
	};
}
