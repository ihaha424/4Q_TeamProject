#pragma once

#include "SystemInterfaceStructure.h"

namespace PhysicsEngineAPI
{
	__INTERFACE__
	EXTERN_C class PHYSICS_API IPhysicsSystem
		: public ICreate
		, public IUpdate
		, public IFactory
		, public IBase
	{
	public:
		enum class PhysicsType
		{
			Physx,
			MyPhysx,
			End
		};
		using enum PhysicsType;

		virtual ~IPhysicsSystem() = default;

	protected:
		void SetSecneNumber(IScene* scene, unsigned int _sceneNumber);
	};

	EXTERN_C  bool PHYSICS_API CreateSystem(_OUT_ IPhysicsSystem** physicsSystem, IPhysicsSystem::PhysicsType flag);

}

