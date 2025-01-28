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

	namespace Content::Factory
	{
		template <typename T>
		class Factory
		{
		public:
			~Factory()
			{
				std::ranges::for_each(_origins | std::views::values, Utility::SafeDelete());
				_origins.clear();
			}

			template <typename U, typename... Args> requires std::derived_from<U, T>&& std::constructible_from<U, Args...>
			void Register(Args&&... arguments)
			{
				std::type_index type = typeid(U);
				if (_origins.contains(type)) return;
				_origins[type] = new U(std::forward<Args>(arguments)...);
			}

			template <typename U> requires std::derived_from<U, T>
			U* Copy()
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
