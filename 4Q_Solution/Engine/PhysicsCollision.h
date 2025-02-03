#pragma once

namespace Engine::Physics
{
	// Client Interface
	struct ICollision
	{
		ICollision() = default;
		ICollision(const ICollision& other) = default;
		ICollision(ICollision&& other) noexcept = default;
		ICollision& operator=(const ICollision& other) = default;
		ICollision& operator=(ICollision&& other) noexcept = default;
		virtual ~ICollision() = default;
	};

	// Engine Interface
	struct Collision : ICollision
	{
		virtual void FixedUpdate() = 0;
		virtual void Release() = 0;

		/********************************
					Collision
		*********************************/
		virtual void BindCollision(const Physics::CallBackTrigger& callback, Physics::TriggerType type) = 0;
		virtual void BindCollision(const Physics::CallBackContact& callback, Physics::ContactType type) = 0;
	};



	namespace CollisionFunction
	{
		template <typename T>
		concept HasOnTriggerEnter = requires(T obj) { { obj.OnTriggerEnter() } -> std::same_as<void>; };
		template <typename T>
		concept HasOnTrigger = requires(T obj) { { obj.OnTrigger() } -> std::same_as<void>; };
		template <typename T>
		concept HasOnTriggerExit = requires(T obj) { { obj.OnTriggerExit() } -> std::same_as<void>; };
		template <typename T>
		concept HasOnCollisionEnter = requires(T obj) { { obj.OnCollisionEnter() } -> std::same_as<void>; };
		template <typename T>
		concept HasOnCollision = requires(T obj) { { obj.OnCollision() } -> std::same_as<void>; };
		template <typename T>
		concept HasOnCollisionExit = requires(T obj) { { obj.OnCollisionExit() } -> std::same_as<void>; };
		template <typename T>
		concept HasOnHit = requires(T obj) { { obj.OnHit() } -> std::same_as<void>; };
		template <typename T>
		concept HasOnOverlapBegin = requires(T obj) { { obj.OnOverlapBegin() } -> std::same_as<void>; };
		template <typename T>
		concept HasOnOverlapEnd = requires(T obj) { { obj.OnOverlapEnd() } -> std::same_as<void>; };

		template <typename T>
		concept HasCollision =
			HasOnTriggerEnter<T> || HasOnTrigger<T> || HasOnTriggerExit<T> ||
			HasOnCollisionEnter<T> || HasOnCollision<T> || HasOnCollisionExit<T> ||
			HasOnHit<T> || HasOnOverlapBegin<T> || HasOnOverlapEnd<T>;

		template <typename T>
		concept NonCollision = !HasCollision<T>;
	}
}
