#pragma once
#include "IShape.h"
#include "PhysXActorFunction.h"
#include "PhysXUtils.h"


namespace PhysicsEngineAPI
{
	class PhysXShape
		: public IShape
	{
	public:
		explicit	PhysXShape(physx::PxShape* shape);
		virtual		~PhysXShape();

		/**
		 * @brief		:Set The Collistion Trigger
						Default is Collision.
						A shape cannot be both a simulation and a trigger at the same time.
		 * @param flag	: Collision Flag
		 * @param value	: true/false.
		 */
		void SetFlag(Utils::DataStructure::CollisionType flag, bool value) override;
	
		
		void SetLocalTranslate(const Utils::Math::Vector3& LocalTranslate)	override; 
		const Utils::Math::Vector3 GetLocalTranslate() const				override;

		void SetLocalRotation(const Utils::Math::Vector4& LocalRotation)	override; 
		const Utils::Math::Vector4 GetLocalRotation() const				override;

		void SetLocalTransform(const Utils::Math::Transform& LocalTransform)	override; 
		const Utils::Math::Transform GetLocalTransform() const					override;

		void SetScale(const Utils::Math::Vector3& Scale)	override;
		const Utils::Math::Vector3 GetScale() const		override;

		
		void SetName(const char* Name) override; 
		const char* GetName() const override;

		void SetUserData(ICollision* UserData)	override; 
		const ICollision* GetUserData() const	override;
		void ClearUserData()					override;
		
		physx::PxShape* operator->() { return shape; }

	public:
		void Release() override;

	private:
		physx::PxShape* shape;

		friend class PhysXActorFunction;
		friend class PhysXSystem;
	};
}

