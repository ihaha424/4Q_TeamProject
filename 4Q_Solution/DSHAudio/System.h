#pragma once

namespace DSH::Audio
{
	class System final : public ISystem
	{
	public:
		System();
		System(const System& other) = default;
		System(System&& other) noexcept = default;
		System& operator=(const System& other) = default;
		System& operator=(System&& other) noexcept = default;
		~System() override;

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		void Update() override;

		HRESULT CreateSound(const std::filesystem::path& path, ChannelGroupType group, bool isLoop, ISound** ppSound) override;

		HRESULT Pause() override;
		HRESULT Pause(ChannelGroupType group) override;

		HRESULT Resume() override;
		HRESULT Resume(ChannelGroupType group) override;

		HRESULT Stop() override;
		HRESULT Stop(ChannelGroupType group) override;

		HRESULT SetVolume(float volume) override;
		HRESULT SetVolume(ChannelGroupType group, float volume) override;

		HRESULT Mute() override;
		HRESULT Mute(ChannelGroupType group) override;

		HRESULT Unmute() override;
		HRESULT Unmute(ChannelGroupType group) override;

	private:
		FMOD::System* _system;
		FMOD::ChannelGroup* _masterGroup;
		std::unordered_map<ChannelGroupType, FMOD::ChannelGroup*> _channelGroups;
	};
}
