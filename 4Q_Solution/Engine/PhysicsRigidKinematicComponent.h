#pragma once

namespace Engine::Physics
{
	struct IRigidKinematicComponent
	{

	};

	struct RigidKinematicComponent : IRigidKinematicComponent, RigidDynamicComponent
	{

	};
}
