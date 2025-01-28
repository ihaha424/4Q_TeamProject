#pragma once

namespace Engine
{
	class Object;

	class World
	{
	public:
		World() = default;
		World(const World& other) = default;
		World(World&& other) noexcept = default;
		World& operator=(const World& other) = default;
		World& operator=(World&& other) noexcept = default;
		virtual ~World() = default;

		virtual void Prepare(Content::Factory::Object* objectFactory) = 0;

		virtual void PreInitialize(const Modules& modules);
		virtual void PostInitialize(const Modules& modules);
		virtual void PreAttach();
		virtual void PostAttach();
		virtual void PreUpdate(float deltaTime);
		virtual void PostUpdate(float deltaTime);
		virtual void PreFixedUpdate();
		virtual void PostFixedUpdate();
		virtual void PreDetach();
		virtual void PostDetach();
		virtual void PreFinalize();
		virtual void PostFinalize();
	};
}
