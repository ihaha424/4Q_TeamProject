#include "pch.h"
#include "PhysXMaterial.h"

namespace PhysicsEngineAPI
{
	PhysXMaterial::PhysXMaterial(physx::PxMaterial* _material)
		: material{ _material }
	{}
	PhysXMaterial::~PhysXMaterial() { Release(); }
	void PhysXMaterial::Release() { SAFE_RELEASE(material); }



	const physx::PxMaterial* PhysXMaterial::GetMaterial() const
	{
		return material;
	}

}

