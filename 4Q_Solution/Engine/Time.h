#pragma once

namespace Engine::Manager
{
	class Time
	{
	public:
		Time() = default;

		void Initialize();
		void Tick() const;
		void Finalize();

		[[nodiscard]] float GetDeltaTime() const;
		[[nodiscard]] float GetDeltaMetaTime() const;

	private:
		DSH::Time::ISystem* _system;
		DSH::Time::ITickTimer* _tickTimer;
	};
}

