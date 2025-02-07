#pragma once

namespace DSH::Audio
{
	class Sound3D final : public ISound3D
	{
	public:
		Sound3D(FMOD::System* system, FMOD::ChannelGroup* group, const std::filesystem::path& path, bool isLoop);
		~Sound3D() override;

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		HRESULT Play() override;
		HRESULT Stop() override;
		[[nodiscard]] bool IsPlaying() const override;

		HRESULT Pause() override;
		HRESULT Resume() override;
		[[nodiscard]] bool IsPaused() const override;

		HRESULT SetVolume(float volume) override;
		[[nodiscard]] float GetVolume() const override;

		HRESULT Mute() override;
		HRESULT Unmute() override;
		[[nodiscard]] bool IsMuted() const override;

		HRESULT FadeIn(float fadeTime) override;
		HRESULT FadeOut(float fadeTime) override;

		HRESULT SetDelay(float delayTime) override;

		[[nodiscard]] float GetLength() const override;

		HRESULT SetPosition(const Vector& position) override;
		HRESULT SetVelocity(const Vector& velocity) override;

	private:
		[[nodiscard]] unsigned long long GetDspClock() const;
		[[nodiscard]] unsigned long long GetSampleRateTime(float time) const;
		[[nodiscard]] unsigned int GetPosition() const;

		ULONG _referenceCount;

		FMOD::System* _system;
		FMOD::Channel* _channel;
		FMOD::Sound* _sound;
		FMOD::ChannelGroup* _group;
		int _rate;

		Vector _position;
		Vector _velocity;
	};
}
