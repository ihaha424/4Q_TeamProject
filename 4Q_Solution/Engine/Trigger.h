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

			virtual void SetComponent(Component::IButtonComponent* component) = 0;
			virtual void SetComponent(Component::IAxisComponent* component) = 0;

			virtual void AddModifier(Modifier::INegative* modifier) = 0;
			virtual void AddModifier(Modifier::ISwizzleAxis* modifier) = 0;
		};
	}
}
