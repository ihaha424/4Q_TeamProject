#pragma once

namespace Engine::Physics
{
	enum class PhysicsType
	{
		Physx,
		MyPhysics,

		End
	};

	struct SceneDesc
	{
		/**
		 * @brief	: gravity
		 */
		Engine::Math::Vector3 gravity;
		/**
		 * @brief	: CPUDispatcherCount
		 */
		unsigned int CPUDispatcherCount;
	};
}