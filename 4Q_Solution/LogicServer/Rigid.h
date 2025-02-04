#pragma once

#include "Physics/InterfaceAPI.h"
#include "../Engine/Math.h"
#include "../Engine/Transform.h"
#include "../Engine/PhysicsUtils.h"
#include "../Engine/Physics.h"
#include "../Engine/PHICoordinateConvert.h"
#include "../Engine/PHIManager.h"

class Object;

namespace Sever::Component
{
	struct Rigid
	{
		Engine::Physics::IRigidComponent* _rigidBody;
		Engine::Physics::IRigidStaticComponent* _staticRigid;
		Engine::Physics::IRigidKinematicComponent* _kinematicRigid;
		Engine::Physics::IRigidDynamicComponent* _dynamicRigid;
		Engine::Physics::Controller* _dynamicRigid;


		Object* Owner;
	};
};
