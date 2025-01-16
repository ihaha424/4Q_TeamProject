#pragma once

namespace DSH::Time
{
	EXTERN_C const IID IID_ITickTimer;

	EXTERN_C MIDL_INTERFACE("faa968a7-b970-4f68-a1b2-9eff34fbca47")
		DSH_TIME_LIBRARY_API ITickTimer : IUnknown
	{
		ITickTimer() = default;
		ITickTimer(const ITickTimer& other) = default;
		ITickTimer(ITickTimer&& other) noexcept = default;
		ITickTimer& operator=(const ITickTimer& other) = default;
		ITickTimer& operator=(ITickTimer&& other) noexcept = default;
		virtual ~ITickTimer() = default;

		virtual void STDMETHODCALLTYPE Tick() noexcept = 0;

		[[nodiscard]] virtual FLOAT STDMETHODCALLTYPE GetDeltaMetaTime() const noexcept = 0;

		[[nodiscard]] virtual FLOAT STDMETHODCALLTYPE GetDeltaTime() const noexcept = 0;

		virtual FLOAT STDMETHODCALLTYPE SetTimeScale(
			/* [annotation][in] */
			_In_ FLOAT timeScale) noexcept = 0;

		[[nodiscard]] virtual FLOAT STDMETHODCALLTYPE GetTimeScale() const noexcept = 0;
	};
}