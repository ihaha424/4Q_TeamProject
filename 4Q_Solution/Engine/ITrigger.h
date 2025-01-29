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
		enum class Event : unsigned char
		{
			Triggered = 4,
			Started = 2,
			Ongoing = 0,
			Completed = 1,
			Canceled = 3
		};

		struct ITrigger
		{
			ITrigger() = default;
			ITrigger(const ITrigger& other) = default;
			ITrigger(ITrigger&& other) noexcept = default;
			ITrigger& operator=(const ITrigger& other) = default;
			ITrigger& operator=(ITrigger&& other) noexcept = default;
			virtual ~ITrigger() = default;

			virtual void SetComponent(Component::IButtonComponent* component) = 0;
			virtual void SetComponent(Component::IAxisComponent* component) = 0;

			virtual void AddModifier(Modifier::INegative* modifier) = 0;
			virtual void AddModifier(Modifier::ISwizzleAxis* modifier) = 0;
		};
	}
}
