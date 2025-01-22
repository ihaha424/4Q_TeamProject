#include "pch.h"
#include "PhysXUtils.h"

namespace Physics
{
	physx::PxVec3 Vector3ToPxVec3(const Utils::Math::Vector3& vector3)
	{
		return physx::PxVec3{vector3.x, vector3.y, vector3.z};
	}
	Utils::Math::Vector3 PxVec3ToVector3(const physx::PxVec3& pxVec3)
	{
		return Utils::Math::Vector3{pxVec3.x, pxVec3.y, pxVec3.z};
	}

	physx::PxVec4 Vector4ToPxVec4(const Utils::Math::Vector4& vector4)
	{
		return physx::PxVec4{vector4.x, vector4.y, vector4.z, vector4.w};
	}
	Utils::Math::Vector4 PxVec4ToVector4(const physx::PxVec4& pxVec4)
	{
		return Utils::Math::Vector4{pxVec4.x, pxVec4.y, pxVec4.z, pxVec4.w};
	}

	physx::PxTransform TransformToPxTransform(const Utils::Math::Transform& transform)
	{
		return physx::PxTransform{{ transform.position.x, transform.position.y, transform.position.z }, { transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w }};
	}
	Utils::Math::Transform PxTransformToTransform(const physx::PxTransform& pxTransform)
	{
		return Utils::Math::Transform{{ pxTransform.p.x, pxTransform.p.y, pxTransform.p.z }, { pxTransform.q.x, pxTransform.q.y, pxTransform.q.z, pxTransform.q.w }};
	}
}
