#pragma once

namespace Engine::DSHAudio
{
	class Manager final : public Audio::Manager
	{
	public:
		Manager() = default;

		void Initialize() override;
		void Update() override;
		void Finalize() override;

		void CreateSound(const std::filesystem::path& path, bool isBackground, bool isLoop, DSH::Audio::ISound** sound) const;
		void CreateSound(const std::filesystem::path& path, DSH::Audio::ISound3D** sound) const;

		void CreateListener(DSH::Audio::IListener** listener) const;

	private:
		DSH::Audio::ISystem* _system;
	};
}
