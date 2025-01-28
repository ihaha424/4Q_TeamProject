#pragma once

namespace Engine
{
	struct Modules;

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

		virtual void Prepare(Content::Factory::Component* componentFactory) = 0;
		void Dispose();
		[[nodiscard]] bool IsDisposed() const;

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

	protected:
		virtual void DisposeComponents() = 0;

		Transform _transform;
		bool _isDispose;

		// TODO: Owner
	};
}
