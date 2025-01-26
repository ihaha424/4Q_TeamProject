#pragma once

namespace Engine::PHI
{
	class RigidStaticComponent final
		: public Physics::RigidStaticComponent
	{
		/********************************
					Rigid Object
		*********************************/
		void SetTranslate(const Math::Vector3& position) override;
		const Math::Vector3 GetTranslate() const override;
		void SetRotation(const Math::Quaternion& Rotation) override;
		const Math::Quaternion GetRotation() const override;
		void SetTransform(const Transform& transform) override;
		const Transform GetTransform() const override;

		void* GetPhysicsObject() const override;


		/********************************
					   Shape
		*********************************/
		void SetFlag(Physics::CollisionType flag, bool value) override;
		void SetLocalTranslate(const Math::Vector3& LocalTranslate) override;
		const Math::Vector3 GetLocalTranslate() const override;
		void SetLocalRotation(const Math::Quaternion& LocalRotation) override;
		const Math::Quaternion GetLocalRotation() const override;
		void SetLocalTransform(const Transform& LocalTransform) override;
		const Transform GetLocalTransform() const override;
		void SetScale(const Math::Vector3& Scale) override;
		const Math::Vector3 GetScale() const override;

		/********************************
					Geometry
		*********************************/
		void SetType(Physics::GeometryShape type) override;
		Physics::GeometryShape GetType() override;
		const void* GetGeometry() const override;

		/********************************
				Engine Life Cycle
		*********************************/
		void Initialize() override;
		void Update(float deltaTime) const override;
		void Finalize() override;

	protected:
		PhysicsEngineAPI::IObject* object;
		PhysicsEngineAPI::IShape* shape;
		PhysicsEngineAPI::IGeometry* geometry;
		PhysicsEngineAPI::IMaterial* material;
	};
}


