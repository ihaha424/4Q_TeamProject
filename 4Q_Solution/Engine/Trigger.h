#pragma once

namespace Engine::Input
{
	namespace Component
	{
		struct IComponent;
	}

	namespace Modifier
	{
		struct IModifier;
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

			virtual void SetComponent(Component::IComponent* component) = 0;
			virtual void SetModifier(Modifier::IModifier* modifier) = 0;
		};
	}
}
