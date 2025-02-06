#pragma once

namespace Engine
{
	class Object;
}

namespace Engine::Component
{
	class Component;
}

namespace Engine::Physics
{
	// Engine Interface
	struct Component
	{
		Component() = default;
		Component(const Component& other) = default;
		Component(Component&& other) noexcept = default;
		Component& operator=(const Component& other) = default;
		Component& operator=(Component&& other) noexcept = default;
		virtual ~Component() = default;

		virtual void SetOwner(void* owner) = 0;
		virtual void* GetOwner() = 0;
	};
}

