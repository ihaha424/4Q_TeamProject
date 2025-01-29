#pragma once

namespace Engine::Time
{
	struct IManager
	{
		IManager() = default;
		IManager(const IManager& other) = default;
		IManager(IManager&& other) noexcept = default;
		IManager& operator=(const IManager& other) = default;
		IManager& operator=(IManager&& other) noexcept = default;
		virtual ~IManager() = default;

		[[nodiscard]] virtual float GetDeltaTime() const = 0;
		[[nodiscard]] virtual float GetDeltaMetaTime() const = 0;
	};

	struct Manager : IManager
	{
		virtual void Initialize(float fixedUpdateInterval) = 0;
		virtual void Tick() = 0;
		virtual bool IsFixedUpdate() = 0;
		virtual void Finalize() = 0;
	};
}
