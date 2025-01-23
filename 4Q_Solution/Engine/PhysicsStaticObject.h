#pragma once
#include "PhysicsObject.h"

namespace Engine::Physics
{
	struct IStaticObject
		: IObject
	{
	};

	struct StaticObject
		: IStaticObject
	{
	};
}
