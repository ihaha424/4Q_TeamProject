#pragma once

namespace Engine::Input
{
	enum class TriggerType : unsigned char
	{
		Down,
		// TODO: Add more trigger types.
	};

	struct IAction
	{
		IAction() = default;
		IAction(const IAction& other) = default;
		IAction(IAction&& other) noexcept = default;
		IAction& operator=(const IAction& other) = default;
		IAction& operator=(IAction&& other) noexcept = default;
		virtual ~IAction() = default;

		virtual void AddTrigger(TriggerType triggerType, Device::IMouse::Button button) = 0;
	};

	struct Action : IAction
	{
	};
}