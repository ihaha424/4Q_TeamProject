#pragma once

namespace Engine::DSHTime
{
	class Manager final: public Time::Manager
	{
	public:
		Manager();

		void Initialize() override;
		void Tick() const override;
		void Finalize() override;

		[[nodiscard]] float GetDeltaTime() const override;
		[[nodiscard]] float GetDeltaMetaTime() const override;

	private:
		DSH::Time::ISystem* _system;
		DSH::Time::ITickTimer* _tickTimer;
	};
}
