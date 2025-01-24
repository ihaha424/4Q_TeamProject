#pragma once

#include "IMaterial.h"
#include "PhysXUtils.h"
#include "PhysXScene.h"

namespace PhysicsEngineAPI
{
	class PhysXMaterial
		: public IMaterial
	{
	public:
		explicit	PhysXMaterial(physx::PxMaterial* material);
		virtual		~PhysXMaterial();

		const physx::PxMaterial* GetMaterial() const;

		physx::PxMaterial* operator->() { return material; }


	public:
		void Release() override;

	private:
		physx::PxMaterial* material;

		friend class PhysXSystem;
	};
}

