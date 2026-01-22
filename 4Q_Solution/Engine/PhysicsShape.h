#pragma once

namespace Engine::Physics
{
	// Engine Interface
	struct Shape
	{
		Shape() = default;
		Shape(const Shape& other) = default;
		Shape(Shape&& other) noexcept = default;
		Shape& operator=(const Shape& other) = default;
		Shape& operator=(Shape&& other) noexcept = default;
		virtual ~Shape() = default;

		virtual void SetFlag(CollisionType flag, bool value) = 0;

		virtual void SetLocalTranslate(const Engine::Math::Vector3& LocalTranslate) = 0;
		virtual  Engine::Math::Vector3 GetLocalTranslate()const				= 0;

		virtual void SetLocalRotation(const Engine::Math::Vector4& LocalRotation)	= 0;
		virtual  Engine::Math::Vector4 GetLocalRotation() const				= 0;

		virtual void SetLocalTransform(const Engine::Transform& LocalTransform) = 0;
		virtual  Engine::Transform GetLocalTransform() const				= 0;

		virtual void SetScale(const Engine::Math::Vector3& Scale)	= 0;
		virtual  Engine::Math::Vector3 GetScale() const		= 0;
	};
}
