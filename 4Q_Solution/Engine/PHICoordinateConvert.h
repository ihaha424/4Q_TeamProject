#pragma once

namespace Engine::PHI::CONVERT
{
	inline Engine::Math::Vector3 PhysicsVector3ToVector3(const PhysicsEngineAPI::Utils::Math::Vector3& vector3);
	inline PhysicsEngineAPI::Utils::Math::Vector3 Vector3ToPhysicsVector3(const Engine::Math::Vector3& vector3);
	
	inline Engine::Math::Vector4 PhysicsVector4ToVector4(const PhysicsEngineAPI::Utils::Math::Vector4& vector4);
	inline PhysicsEngineAPI::Utils::Math::Vector4 Vector4ToPhysicsVector4(const Engine::Math::Vector4& vector4);
	
	inline Engine::Math::Quaternion PhysicsVector4ToQuaternion(const PhysicsEngineAPI::Utils::Math::Vector4& vector4);
	inline PhysicsEngineAPI::Utils::Math::Vector4 QuaternionToPhysicsVector4(const Engine::Math::Quaternion& vector4);

	inline Engine::Transform PhysicsTransformToTransform(const PhysicsEngineAPI::Utils::Transform& transform);
	inline PhysicsEngineAPI::Utils::Transform TransformToPhysicsTransform(const Engine::Transform& transform);
};

using namespace Engine::PHI::CONVERT;