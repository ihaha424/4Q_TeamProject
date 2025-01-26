#pragma once

namespace Engine::PHI
{
	class RigidDynamicComponent final
		: public Physics::RigidDynamicComponent
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
				Rigid Dynamic
				Transform Associate
		*********************************/
		void SetVelocity(const Engine::Math::Vector3& velocity) override;
		const Engine::Math::Vector3 GetVelocity() const override;

		void SetLinearVelocity(const Engine::Math::Vector3& velocity) override;
		const Engine::Math::Vector3 GetLinearVelocity() const override;

		void SetMaxLinearVelocity(const float velocity) override;
		const float GetMaxLinearVelocity() const override;

		void SetAngularVelocity(const Engine::Math::Vector3& angularVelocity) override;
		const Engine::Math::Vector3 GetAngularVelocity() const override;

		void SetMaxAngularVelocity(const float velocity) override;
		const float GetMaxAngularVelocity() const override;


		/********************************
				Rigid Dynamic
				Force Associate
		*********************************/
		void AddForce(const Engine::Math::Vector3& force) override;
		void AddTorque(const Engine::Math::Vector3& force) override;
		void ClearForce() override;
		void ClearTorque() override;


		/********************************
				Rigid Dynamic
				State Associate
		*********************************/
		void Wakeup() override;
		bool IsSleeping() override;
		void PutToSleep() override;
		void SetSleepThreshold() override;
		void SetWakeCounter(float timer) override;
		float GetWakeCounter() override;


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
		PhysicsEngineAPI::IDynamicObject* object;
		PhysicsEngineAPI::IShape* shape;
		PhysicsEngineAPI::IGeometry* geometry;
		PhysicsEngineAPI::IMaterial* material;
	};

}

