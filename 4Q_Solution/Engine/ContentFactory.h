#pragma once
#include "SafeDelete.h"

namespace Engine
{
	class World;
	class Object;
	namespace Component
	{
		class Component;
	}

	namespace Content
	{
		template <typename T>
		concept is_content = std::derived_from<T, World> || std::derived_from<T, Object> || std::derived_from<T, Component::Component>;

		template <is_content T>
		class Factory
		{
		public:
			~Factory()
			{
				std::ranges::for_each(_origins | std::views::values, Utility::SafeDelete());
				_origins.clear();
			}

			template <typename U, typename... Args> requires std::derived_from<U, T>&& std::constructible_from<U, Args...>
			void Register(Args... arguments)
			{
				std::type_index type = typeid(U);
				if (_origins.contains(type)) return;
				_origins[type] = new U(arguments...);
			}

			template <typename U> requires std::derived_from<U, T>
			U* Clone()
			{
				U* clone = nullptr;
				std::type_index type = typeid(U);
				if (auto origin = _origins.find(type); 
					origin != _origins.end())
				{
					if (const U* casted = dynamic_cast<U*>(origin->second))
					{
						clone = new U(*casted);
					}
				}
				return clone;
			}

		private:
			std::unordered_map<std::type_index, T*> _origins;
		};
	}
}
