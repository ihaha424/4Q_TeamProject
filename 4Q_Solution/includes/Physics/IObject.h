#pragma once

#include "IUserData.h"

namespace PhysicsEngineAPI
{
	class IShape;
}

namespace PhysicsEngineAPI
{
	__INTERFACE__
	EXTERN_C class PHYSICS_API IObject
		: public IUserData
		, public IBase
	{
	public:
		virtual ~IObject() = default;


		virtual bool	AttachShape(IShape* shape) = 0;
		virtual bool	DetachShape(IShape* shape) = 0;

		virtual void	SetTranslate(const Utils::Math::Vector3& position)	= 0;
		virtual 	Utils::Math::Vector3 GetTranslate() const			= 0;

		virtual void	SetRotation(const Utils::Math::Vector4& Rotation)	= 0;
		virtual 	Utils::Math::Vector4 GetRotation() const			= 0;

		virtual void	SetTransform(const Utils::Math::Transform& transform)	= 0;
		virtual 	Utils::Math::Transform GetTransform() const				= 0;

		virtual void*	GetPhysicsObject() = 0;
	public:
		// Todo:
		// physx::PxActorFlag

		// Delete Todo:
		// Physx에서는 지원하지 않음, 필요시 만들기
		// Object의 계층구조는 없으나 유사하게PxArticulation(관절)을 통해 구현할 수 있음
		//virtual void	SetLocalTranslate(const Utils::Math::Vector3& position) = 0;
		//virtual const	Utils::Math::Vector3 GetLocalTranslate() const = 0;

		//virtual void	SetLocalRotation(const Utils::Math::Vector4& Rotation) = 0;
		//virtual const	Utils::Math::Vector4 GetLocalRotation() const = 0;

		//virtual void	SetLocalTransform(const Utils::Math::Transform& transform) = 0;
		//virtual const	Utils::Math::Transform GetLocalTransform() const = 0;
	};
}
