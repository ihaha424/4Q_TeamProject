#pragma once

namespace Engine::Input
{
	struct IAction
	{
		using Listener = std::function<void(const Value& value)>;
		IAction() = default;
		IAction(const IAction& other) = default;
		IAction(IAction&& other) noexcept = default;
		IAction& operator=(const IAction& other) = default;
		IAction& operator=(IAction&& other) noexcept = default;
		virtual ~IAction() = default;

		virtual void GetTrigger(Trigger::IDown** trigger) = 0;

		virtual void AddListener(Trigger::Event event, Listener listener) = 0;
	};

	struct Action : IAction
	{
		virtual void Finalize() = 0;
	};
}