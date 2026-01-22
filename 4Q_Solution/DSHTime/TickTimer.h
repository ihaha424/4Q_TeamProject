#pragma once

namespace DSH::Time
{
	class TickTimer final : public ITickTimer
	{
	public:
		TickTimer();

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		void Tick() noexcept override;
		[[nodiscard]] FLOAT GetDeltaMetaTime() const noexcept override;
		[[nodiscard]] FLOAT GetDeltaTime() const noexcept override;
		FLOAT SetTimeScale(FLOAT timeScale) noexcept override;
		[[nodiscard]] FLOAT GetTimeScale() const noexcept override;

	private:
		ULONG _referenceCount;

		std::chrono::steady_clock::time_point _currentTime;
		std::chrono::steady_clock::time_point _previousTime;
		FLOAT _deltaTime;
		FLOAT _timeScale;
	};
}
