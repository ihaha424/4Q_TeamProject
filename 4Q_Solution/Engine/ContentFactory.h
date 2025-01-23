#pragma once

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
				for (const T* origin : _origins)
				{
					delete origin;
				}
				_origins.clear();
			}

			template <typename U, typename... Args> requires std::derived_from<U, T>&& std::constructible_from<U, Args...>
			void Register(Args... arguments)
			{
				std::tuple<Args...> tArguments{ arguments... };
				_origins.push_back(new T(arguments...));
			}

		private:
			std::unordered_set<T*> _origins;
		};
	}
}
