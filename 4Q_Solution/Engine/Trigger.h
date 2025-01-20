#pragma once

namespace Engine::Input
{
	namespace Component
	{
		struct Component;
	}

	namespace Modifier
	{
		struct Modifier;
	}

	namespace Trigger
	{
		struct Trigger
		{
			Trigger() = default;
			Trigger(const Trigger& other) = default;
			Trigger(Trigger&& other) noexcept = default;
			Trigger& operator=(const Trigger& other) = default;
			Trigger& operator=(Trigger&& other) noexcept = default;
			virtual ~Trigger() = default;

			virtual void SetComponent(Component::Component* component) = 0;
			virtual void SetModifier(Modifier::Modifier* modifier) = 0;
		};
	}
}
