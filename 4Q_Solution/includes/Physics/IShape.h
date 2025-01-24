#pragma once

#include "ICollision.h"
#include "IUserData.h"

namespace PhysicsEngineAPI
{
	__INTERFACE__
	EXTERN_C class PHYSICS_API IShape
		: public IUserData
		, public IBase
	{
	public:
		virtual ~IShape() = default;


		virtual void SetFlag(Utils::DataStructure::CollisionType flag, bool value) = 0;
	

		virtual void SetLocalTranslate(const Utils::Math::Vector3& LocalTranslate)	= 0; 
		virtual const Utils::Math::Vector3 GetLocalTranslate()const				= 0;

		virtual void SetLocalRotation(const Utils::Math::Vector4& LocalRotation)	= 0; 
		virtual const Utils::Math::Vector4 GetLocalRotation() const				= 0;

		virtual void SetLocalTransform(const Utils::Math::Transform& LocalTransform)	= 0; 
		virtual const Utils::Math::Transform GetLocalTransform() const					= 0;
		
		virtual void SetScale(const Utils::Math::Vector3& Scale)	= 0; 
		virtual const Utils::Math::Vector3 GetScale() const		= 0;
	};
}

