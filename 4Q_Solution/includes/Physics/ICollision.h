#pragma once
#include <concepts>

namespace PhysicsEngineAPI
{
	//enum class CollisionObjectType
	//{
	//	Object,
	//	Shape,

	//	End
	//};
	
	//ColliderComponent가 이것을 상속받아서 만들도록
	//TODO: Fetch에서 Colllision이 발생하고
	//		-> 이것의 의해 아직 패치 중임으로 Actor에게 무엇인가 실행시키는 것은 안된다.
	//		-> flag나 Event방식으로 끝나고 동기화 처리해서 한번에 처리 해야함.
	__INTERFACE__
	EXTERN_C class PHYSICS_API ICollision
	{
	public:
		// Refer. Unity Collosion
		virtual void __CALLBACK__ OnTriggerEnter()		= 0;
		virtual void __CALLBACK__ OnTrigger()			= 0;
		virtual void __CALLBACK__ OnTriggerExit()		= 0;
		virtual void __CALLBACK__ OnCollisionEnter()	= 0;
		virtual void __CALLBACK__ OnCollision()			= 0;
		virtual void __CALLBACK__ OnCollisionExit()		= 0;

		// Refer. Unreal Collosion
		virtual void __CALLBACK__ OnHit()			= 0;
		virtual void __CALLBACK__ OnOverlapBegin()	= 0;
		virtual void __CALLBACK__ OnOverlapEnd()	= 0;
	};





















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
	concept Collision =
		HasOnTriggerEnter<T> || HasOnTrigger<T> || HasOnTriggerExit<T> ||
		HasOnCollisionEnter<T> || HasOnCollision<T> || HasOnCollisionExit<T> ||
		HasOnHit<T> || HasOnOverlapBegin<T> || HasOnOverlapEnd<T>;

	template <typename T>
	concept NonCollision = !Collision<T>;
}
