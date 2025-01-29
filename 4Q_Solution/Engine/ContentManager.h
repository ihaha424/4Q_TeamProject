#pragma once

namespace Engine
{
	class World;
	class Object;
	struct Modules;

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

			virtual Factory::World* GetWorldFactory() = 0;
			virtual Factory::Object* GetObjectFactory() = 0;
			virtual Factory::Component* GetComponentFactory() = 0;
		};

		struct Manager : IManager
		{
			virtual void Initialize() = 0;
			virtual void Finalize() = 0;

			virtual void Contraction(const Modules& modules) = 0;
			virtual void Update(float deltaTime) = 0;
			virtual void FixedUpdate() = 0;
			virtual void Relaxation() = 0;
		};
	}

}