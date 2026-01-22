#pragma once
#include "PHICollision.h"

namespace Engine::PHI
{
	class RigidComponent final
		: public Physics::RigidComponent
	{
	public:
		RigidComponent();


		/********************************
					Rigid Object
		*********************************/
		void SetTranslate(const Math::Vector3& position) override;
		 Math::Vector3 GetTranslate() const override;
		void SetRotation(const Math::Quaternion& Rotation) override;
		 Math::Quaternion GetRotation() const override;
		void SetTransform(const Transform& transform) override;
		 Transform GetTransform() const override;
		 Engine::Math::Vector3 GetBounds()const override;



		/********************************
					   Shape
		*********************************/
		void SetFlag(Physics::CollisionType flag, bool value) override;
		void SetLocalTranslate(const Math::Vector3& LocalTranslate) override;
		 Math::Vector3 GetLocalTranslate() const override;
		void SetLocalRotation(const Math::Quaternion& LocalRotation) override;
		 Math::Quaternion GetLocalRotation() const override;
		void SetLocalTransform(const Transform& LocalTransform) override;
		 Transform GetLocalTransform() const override;
		void SetScale(const Math::Vector3& Scale) override;
		 Math::Vector3 GetScale() const override;

		
		/********************************
					Geometry
		*********************************/
		void SetType(Physics::GeometryShape type) override;
		Physics::GeometryShape GetType() override;
		

		/********************************
					Material
		*********************************/


		/********************************
					Collision
		*********************************/
		void BindCollision(const Physics::CallBackTrigger& callback, Physics::TriggerType type) override;
		void BindCollision(const Physics::CallBackContact& callback, Physics::ContactType type) override;

		/********************************
				Engine Life Cycle
		*********************************/
		void Initialize() override;
		void Update(float deltaTime) const override;
		void FixedUpdate() const override;
		void Finalize() override;

		void SetOwner(void* owner) override;
		void* GetOwner() override;
	protected:
		PhysicsEngineAPI::IObject*		object;
		PhysicsEngineAPI::IShape*		shape;
		PhysicsEngineAPI::IGeometry*	geometry;
		PhysicsEngineAPI::IMaterial*	material;

	private:
		Collision<RigidComponent>* collision;
		void* owner;
	private:
		friend class Manager;
		friend class Scene;
	};
}
