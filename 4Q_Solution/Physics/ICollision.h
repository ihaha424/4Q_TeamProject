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
		virtual ~ICollision() = default;

		// Refer. Unity Collosion
		virtual void __CALLBACK__ OnTriggerEnter(Utils::DataStructure::TriggerEvent info)		= 0;
		virtual void __CALLBACK__ OnTrigger(Utils::DataStructure::TriggerEvent info)			= 0;
		virtual void __CALLBACK__ OnTriggerExit(Utils::DataStructure::TriggerEvent info)		= 0;
		virtual void __CALLBACK__ OnCollisionEnter(Utils::DataStructure::ContactEvent info)		= 0;
		virtual void __CALLBACK__ OnCollision(Utils::DataStructure::ContactEvent info)			= 0;
		virtual void __CALLBACK__ OnCollisionExit(Utils::DataStructure::ContactEvent info)		= 0;

		// Refer. Unreal Collosion
		virtual void __CALLBACK__ OnHit(Utils::DataStructure::ContactEvent info)			= 0;
		virtual void __CALLBACK__ OnOverlapBegin(Utils::DataStructure::TriggerEvent info)	= 0;
		virtual void __CALLBACK__ OnOverlapEnd(Utils::DataStructure::TriggerEvent info)		= 0;
	};





















	template <typename T>
	concept HasOnTriggerEnter = requires(T obj, Utils::DataStructure::TriggerEvent info) { { obj.OnTriggerEnter(info) } -> std::same_as<void>; };
	template <typename T>
	concept HasOnTrigger = requires(T obj, Utils::DataStructure::TriggerEvent info) { { obj.OnTrigger(info) } -> std::same_as<void>; };
	template <typename T>
	concept HasOnTriggerExit = requires(T obj, Utils::DataStructure::TriggerEvent info) { { obj.OnTriggerExit(info) } -> std::same_as<void>; };
	template <typename T>
	concept HasOnCollisionEnter = requires(T obj, Utils::DataStructure::ContactEvent info) { { obj.OnCollisionEnter(info) } -> std::same_as<void>; };
	template <typename T>
	concept HasOnCollision = requires(T obj, Utils::DataStructure::ContactEvent info) { { obj.OnCollision(info) } -> std::same_as<void>; };
	template <typename T>
	concept HasOnCollisionExit = requires(T obj, Utils::DataStructure::ContactEvent info) { { obj.OnCollisionExit(info) } -> std::same_as<void>; };
	template <typename T>
	concept HasOnHit = requires(T obj, Utils::DataStructure::ContactEvent info) { { obj.OnHit(info) } -> std::same_as<void>; };
	template <typename T>
	concept HasOnOverlapBegin = requires(T obj, Utils::DataStructure::TriggerEvent info) { { obj.OnOverlapBegin(info) } -> std::same_as<void>; };
	template <typename T>
	concept HasOnOverlapEnd = requires(T obj, Utils::DataStructure::TriggerEvent info) { { obj.OnOverlapEnd(info) } -> std::same_as<void>; };
	template <typename T>
	concept CollisionType =
		HasOnTriggerEnter<T> || HasOnTrigger<T> || HasOnTriggerExit<T> ||
		HasOnCollisionEnter<T> || HasOnCollision<T> || HasOnCollisionExit<T> ||
		HasOnHit<T> || HasOnOverlapBegin<T> || HasOnOverlapEnd<T>;
}
