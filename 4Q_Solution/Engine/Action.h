#pragma once

namespace Engine::Input
{
	struct IAction
	{
		IAction() = default;
		IAction(const IAction& other) = default;
		IAction(IAction&& other) noexcept = default;
		IAction& operator=(const IAction& other) = default;
		IAction& operator=(IAction&& other) noexcept = default;
		virtual ~IAction() = default;

		virtual void GetTrigger(Trigger::IDown** trigger) = 0;
	};

	struct Action : IAction
	{
		virtual void Finalize() = 0;
	};
}