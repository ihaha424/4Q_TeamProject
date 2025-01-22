#include "pch.h"
#include "IPhysicsSystem.h"
#include "PhysXSystem.h"

#include "IScene.h"

namespace Physics
{
    bool CreateSystem(_OUT_ IPhysicsSystem** physicsSystem, IPhysicsSystem::PhysicsType flag)
    {
        if (flag == IPhysicsSystem::PhysicsType::Physx)
        {
            *physicsSystem = new PhysXSystem();
            return true;
        }

        return false;
    }
    void IPhysicsSystem::SetSecneNumber(IScene* scene, unsigned int _sceneNumber)
    {
        scene->sceneNumber = _sceneNumber;
    }
}

