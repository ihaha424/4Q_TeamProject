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

		virtual void Initialize();
		virtual void Attach();
		virtual void Update(float deltaTime);
		virtual void FixedUpdate();
		virtual void Detach();
		virtual void Finalize();

	private:
		std::vector<Component::Component*> _components;
	};
}
