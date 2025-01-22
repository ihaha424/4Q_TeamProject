#include "pch.h"
#include "PhysXMaterial.h"

namespace Physics
{
	PhysXMaterial::PhysXMaterial(physx::PxMaterial* _material)
		: material{ _material }
	{}
	PhysXMaterial::~PhysXMaterial()
	{
		if (material)
			material->release();
	}
	const physx::PxMaterial* PhysXMaterial::GetMaterial() const
	{
		return material;
	}

	void PhysXMaterial::setRestitutionCombineMode()
	{
		material->setRestitutionCombineMode(physx::PxCombineMode::eMULTIPLY);
	}
}

