#pragma once

namespace DSH::Sound
{
	struct ISound;

	EXTERN_C const IID IID_ISystem;

	EXTERN_C MIDL_INTERFACE("cc014ea8-4ca4-4838-8ef7-18006367fd79")
		DSH_SOUND_LIBRARY_API ISystem : IUnknown
	{
		ISystem() = default;
		ISystem(const ISystem& other) = default;
		ISystem(ISystem&& other) noexcept = default;
		ISystem& operator=(const ISystem& other) = default;
		ISystem& operator=(ISystem&& other) noexcept = default;
		virtual ~ISystem() = default;

		virtual void Update() = 0;

		virtual HRESULT CreateSound(
			/* [annotation][in] */
			_In_ const std::filesystem::path& path,
			/* [annotation][in] */
			_In_ ChannelGroupType group,
			/* [annotation][in] */
			_In_ bool isLoop,
			/* [annotation][out] */
			_Out_ ISound** ppSound) = 0;

		virtual HRESULT Pause() = 0;

		virtual HRESULT Pause(
			/* [annotation][in] */
			_In_ ChannelGroupType group) = 0;

		virtual HRESULT Resume() = 0;

		virtual HRESULT Resume(
			/* [annotation][in] */
			_In_ ChannelGroupType group) = 0;

		virtual HRESULT Stop() = 0;

		virtual HRESULT Stop(
			/* [annotation][in] */
			_In_ ChannelGroupType group) = 0;

		virtual HRESULT SetVolume(
			/* [annotation][in] */
			_In_ float volume) = 0;

		virtual HRESULT SetVolume(
			/* [annotation][in] */
			_In_ ChannelGroupType group,
			/* [annotation][in] */
			_In_ float volume) = 0;

		virtual HRESULT Mute() = 0;

		virtual HRESULT Mute(
			/* [annotation][in] */
			_In_ ChannelGroupType group) = 0;

		virtual HRESULT Unmute() = 0;

		virtual HRESULT Unmute(
			/* [annotation][in] */
			_In_ ChannelGroupType group) = 0;
	};
}
