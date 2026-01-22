#pragma once

namespace Engine::Component
{
	class Sound : public Component
	{
	public:
		Sound() = default;

		void SetPath(const std::filesystem::path& path);
		void Finalize() override;

		void Play() const;
		void Stop() const;
		void Pause() const;
		void Resume() const;
		void Mute() const;
		void Unmute() const;

		bool IsPlaying() const;
		bool IsPaused() const;
		bool IsMuted() const;

		void SetVolume(const float volume) const;
		float GetVolume() const;

		void FadeIn(float duration) const;
		void FadeOut(float duration) const;

	protected:
		std::filesystem::path _path;
		DSH::Audio::ISound* _sound;
	};
}