#include "pch.h"
#include "PhysXGeometry.h"

using namespace PhysicsEngineAPI::Utils::DataStructure;

namespace PhysicsEngineAPI
{
	PhysXGeometry::PhysXGeometry(physx::PxGeometry* _geometry)
		: geometry{ _geometry }
	{}

	PhysXGeometry::~PhysXGeometry() { Release(); }
	void PhysXGeometry::Release() { SAFE_DELETE(geometry); }

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
