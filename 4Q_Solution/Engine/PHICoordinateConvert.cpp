#include "pch.h"
#include "PHICoordinateConvert.h"

using namespace Engine::PHI::CONVERT;
namespace Engine::PHI::CONVERT
{
	Engine::Math::Vector3 PhysicsVector3ToVector3(const PhysicsEngineAPI::Utils::Math::Vector3& vector3)
	{
		return Engine::Math::Vector3{ vector3.x, vector3.y, AXIS * vector3.z };
	}
	PhysicsEngineAPI::Utils::Math::Vector3 Vector3ToPhysicsVector3(const Engine::Math::Vector3& vector3)
	{
		return PhysicsEngineAPI::Utils::Math::Vector3{ vector3.x, vector3.y, AXIS * vector3.z};
	}
	Engine::Math::Vector4 PhysicsVector4ToVector4(const PhysicsEngineAPI::Utils::Math::Vector4& vector4)
	{
		return Engine::Math::Vector4{ vector4.x, vector4.y, AXIS * vector4.z, AXIS * vector4.w };
	}
	PhysicsEngineAPI::Utils::Math::Vector4 Vector4ToPhysicsVector4(const Engine::Math::Vector4& vector4)
	{
		return PhysicsEngineAPI::Utils::Math::Vector4{ vector4.x, vector4.y, AXIS * vector4.z, AXIS * vector4.w };
	}
	Engine::Math::Quaternion PhysicsVector4ToQuaternion(const PhysicsEngineAPI::Utils::Math::Vector4& vector4)
	{
		return Engine::Math::Quaternion{Engine::Math::Vector4{ vector4.x, vector4.y, AXIS * vector4.z, AXIS * vector4.w }};
	}
	PhysicsEngineAPI::Utils::Math::Vector4 QuaternionToPhysicsVector4(const Engine::Math::Quaternion& vector4)
	{
		return PhysicsEngineAPI::Utils::Math::Vector4{ vector4.x, vector4.y, AXIS * vector4.z, AXIS * vector4.w };
	}
	Engine::Transform PhysicsTransformToTransform(const PhysicsEngineAPI::Utils::Transform& transform)
	{
		return Engine::Transform{
			Engine::Math::Vector3{ transform.position.x, transform.position.y, AXIS * transform.position.z },
			Engine::Math::Quaternion{ PhysicsEngineAPI::Utils::Vector4{ transform.rotation.x, transform.rotation.y, AXIS * transform.rotation.z, AXIS * transform.rotation.w } },
			Engine::Math::Vector3{ 1.f, 1.f, 1.f }
		};
	}
	PhysicsEngineAPI::Utils::Transform TransformToPhysicsTransform(const Engine::Transform& transform)
	{
		return PhysicsEngineAPI::Utils::Transform{ 
			{ transform.position.x, transform.position.y, AXIS * transform.position.z },
			{ transform.rotation.x, transform.rotation.y, AXIS * transform.rotation.z, AXIS * transform.rotation.w }
		};
	}
}