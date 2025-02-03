#pragma once
#include "Math.h"
#include "Physics/InterfaceAPI.h"

namespace Engine::PHI::CONVERT
{
	Engine::Math::Vector3 PhysicsVector3ToVector3(const PhysicsEngineAPI::Utils::Math::Vector3& vector3);
	PhysicsEngineAPI::Utils::Math::Vector3 Vector3ToPhysicsVector3(const Engine::Math::Vector3& vector3);
	
	Engine::Math::Vector4 PhysicsVector4ToVector4(const PhysicsEngineAPI::Utils::Math::Vector4& vector4);
	PhysicsEngineAPI::Utils::Math::Vector4 Vector4ToPhysicsVector4(const Engine::Math::Vector4& vector4);
	
	Engine::Math::Quaternion PhysicsVector4ToQuaternion(const PhysicsEngineAPI::Utils::Math::Vector4& vector4);
	PhysicsEngineAPI::Utils::Math::Vector4 QuaternionToPhysicsVector4(const Engine::Math::Quaternion& vector4);

	Engine::Transform PhysicsTransformToTransform(const PhysicsEngineAPI::Utils::Transform& transform);
	PhysicsEngineAPI::Utils::Transform TransformToPhysicsTransform(const Engine::Transform& transform);
};

