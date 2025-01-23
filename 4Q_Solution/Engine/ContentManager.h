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
		struct IManager
		{
			IManager() = default;
			IManager(const IManager& other) = default;
			IManager(IManager&& other) noexcept = default;
			IManager& operator=(const IManager& other) = default;
			IManager& operator=(IManager&& other) noexcept = default;
			virtual ~IManager() = default;

			virtual Factory<World>& GetWorldFactory() = 0;
			virtual Factory<Object>& GetObjectFactory() = 0;
			virtual Factory<Component::Component>& GetComponentFactory() = 0;
		};

		struct Manager : IManager
		{
			virtual void Finalize() = 0;
		};
	}

}