#pragma once

namespace Physics
{
	physx::PxVec3 Vector3ToPxVec3(const Utils::Math::Vector3& vector3);
	Utils::Math::Vector3 PxVec3ToVector3(const physx::PxVec3& pxVec3);

	physx::PxVec4 Vector4ToPxVec4(const Utils::Math::Vector4& vector4);
	Utils::Math::Vector4 PxVec4ToVector4(const physx::PxVec4& pxVec4);

	physx::PxTransform TransformToPxTransform(const Utils::Math::Transform& transform);
	Utils::Math::Transform PxTransformToTransform(const physx::PxTransform& pxTransform);
}