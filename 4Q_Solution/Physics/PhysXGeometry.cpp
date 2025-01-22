#include "pch.h"
#include "PhysXGeometry.h"

using namespace Physics::Utils::DataStructure;

namespace Physics
{
	PhysXGeometry::PhysXGeometry(physx::PxGeometry* _geometry)
		: geometry{ _geometry }
	{}

	PhysXGeometry::~PhysXGeometry()
	{
		if (geometry)
			delete geometry;
	}

	const physx::PxGeometry* PhysXGeometry::GetGeometry() const
	{
		return geometry;
	}

	void PhysXGeometry::SetScale(const Utils::Math::Vector3& position)
	{
	}

	const Utils::Math::Vector3 PhysXGeometry::GetScale() const
	{
		return Utils::Math::Vector3();
	}
}
