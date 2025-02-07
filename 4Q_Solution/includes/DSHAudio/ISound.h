#pragma once

namespace DSH::Audio
{
	EXTERN_C const IID IID_ISound;

	EXTERN_C MIDL_INTERFACE("1ea26c4d-e0cf-48ed-991d-5415a34746a3")
		DSH_AUDIO_LIBRARY_API ISound : IUnknown
	{
		ISound() = default;
		ISound(const ISound& other) = default;
		ISound(ISound&& other) noexcept = default;
		ISound& operator=(const ISound& other) = default;
		ISound& operator=(ISound&& other) noexcept = default;
		virtual ~ISound() = default;

        virtual HRESULT Play() = 0;

        virtual HRESULT Stop() = 0;

        [[nodiscard]] virtual bool IsPlaying() const = 0;

        virtual HRESULT Pause() = 0;

        virtual HRESULT Resume() = 0;

        [[nodiscard]] virtual bool IsPaused() const = 0;

        virtual HRESULT SetVolume(
			/* [annotation][in] */
            _In_ float volume) = 0;

        [[nodiscard]] virtual float GetVolume() const = 0;

        virtual HRESULT Mute() = 0;

        virtual HRESULT Unmute() = 0;

        [[nodiscard]] virtual bool IsMuted() const = 0;

        virtual HRESULT FadeIn(
			/* [annotation][in] */
            _In_ float fadeTime = 2.f) = 0;

        virtual HRESULT FadeOut(
			/* [annotation][in] */
            _In_ float fadeTime = 2.f) = 0;

        virtual HRESULT SetDelay(
			/* [annotation][in] */
            _In_ float delayTime = 1.f) = 0;

        [[nodiscard]] virtual float GetLength() const = 0;
	};
}
