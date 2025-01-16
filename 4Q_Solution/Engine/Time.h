#pragma once

namespace Engine::Manager
{
	struct ITime
	{
		ITime() = default;
		ITime(const ITime& other) = default;
		ITime(ITime&& other) noexcept = default;
		ITime& operator=(const ITime& other) = default;
		ITime& operator=(ITime&& other) noexcept = default;
		virtual ~ITime() = default;

		virtual float GetDeltaTime() const = 0;
		virtual float GetDeltaMetaTime() const = 0;
	};

	class Time final : public ITime
	{
	public:
		Time() = default;

		void Initialize();
		void Tick() const;
		void Finalize();

		[[nodiscard]] float GetDeltaTime() const override;
		[[nodiscard]] float GetDeltaMetaTime() const override;

	private:
		DSH::Time::ISystem* _system;
		DSH::Time::ITickTimer* _tickTimer;
	};
}

