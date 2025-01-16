#pragma once

namespace Engine
{
	namespace Component
	{
		class Component;
	}

	class Object
	{
	public:
		Object() = default;
		Object(const Object& other) = default;
		Object(Object&& other) noexcept = default;
		Object& operator=(const Object& other) = default;
		Object& operator=(Object&& other) noexcept = default;
		virtual ~Object() = default;

		void Initialize();
		void Attach();
		void Update(float deltaTime);
		void FixedUpdate();
		void Detach();
		void Finalize();

	protected:
		virtual void PreInitialize();
		virtual void PostInitialize();
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

	private:
		std::vector<Component::Component*> _components;
	};
}
