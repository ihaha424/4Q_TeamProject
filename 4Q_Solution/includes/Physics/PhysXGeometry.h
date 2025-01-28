#pragma once

#include "IGeometry.h"
#include "PhysXUtils.h"
#include "PhysXScene.h"

namespace PhysicsEngineAPI
{
	class PhysXGeometry
		: public IGeometry
	{
	public:
		explicit	PhysXGeometry(physx::PxGeometry* geometry);
		virtual		~PhysXGeometry();
		void Release() override;

		void SetScale(const Utils::Math::Vector3& position) override;
		const Utils::Math::Vector3 GetScale() const override;

		const physx::PxGeometry* GetGeometry() const;
		physx::PxGeometry* operator->() { return geometry; }

		Utils::DataStructure::GeometryShape GetType() override;
	private:
		void SetType(Utils::DataStructure::GeometryShape type) override;

	private:
		physx::PxGeometry* geometry;
		Utils::DataStructure::GeometryShape type = Utils::DataStructure::GeometryShape::End;

		friend class PhysXSystem;
		friend class PhysXScene;
	};
}
