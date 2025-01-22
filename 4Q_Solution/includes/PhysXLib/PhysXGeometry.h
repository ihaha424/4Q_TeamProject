#pragma once

#include "IGeometry.h"
#include "PhysXUtils.h"
#include "PhysXScene.h"

namespace Physics
{
	class PhysXGeometry
		: virtual public IGeometry
	{
	public:
		explicit	PhysXGeometry(physx::PxGeometry* geometry);
		virtual		~PhysXGeometry();

		void SetScale(const Utils::Math::Vector3& position) override;
		const Utils::Math::Vector3 GetScale() const override;

		const physx::PxGeometry* GetGeometry() const;
		physx::PxGeometry* operator->() { return geometry; }
	private:
		physx::PxGeometry* geometry;

		friend class PhysXSystem;
		friend class PhysXScene;
	};
}
