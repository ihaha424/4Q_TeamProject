#pragma once
#include "PhysicsComponent.h"

namespace Engine::PHI
{
	class RigidComponent final
		: public Physics::RigidComponent
	{
		/********************************
					Rigid Object
		*********************************/
		void SetTranslate(const Engine::Math::Vector3& position) override;
		const Engine::Math::Vector3 GetTranslate() const override;
		void SetRotation(const Engine::Math::Vector4& Rotation) override;
		const Engine::Math::Vector4 GetRotation() const override;
		void SetTransform(const Transform& transform) override;
		const Transform GetTransform() const override;


		/********************************
					   Shape
		*********************************/
		bool AttachShape(Shape* shape) override;
		bool DetachShape(Shape* shape) override;
		void SetFlag(CollisionType flag, bool value) override;
		void SetLocalTranslate(const Engine::Math::Vector3& LocalTranslate) override;
		const Engine::Math::Vector3 GetLocalTranslate() const override;
		void SetLocalRotation(const Engine::Math::Vector4& LocalRotation) override;
		const Engine::Math::Vector4 GetLocalRotation() const override;
		void SetLocalTransform(const Engine::Transform& LocalTransform) override;
		const Engine::Transform GetLocalTransform() const override;
		void SetScale(const Engine::Math::Vector3& Scale) override;
		const Engine::Math::Vector3 GetScale() const override;
		
		/********************************
					Geometry
		*********************************/
		GeometryShape SetType(GeometryShape type) override;
		void GetType(GeometryShape type) override;

		/********************************
					Engine
		*********************************/
		void Initialize() override;
		void Update(float deltaTime) const override;
		void Finalize() override;
	};
}
