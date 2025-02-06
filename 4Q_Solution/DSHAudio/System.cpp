#include "pch.h"
#include "System.h"

DSH::Audio::System::System()
{
}

DSH::Audio::System::~System()
{
}

HRESULT DSH::Audio::System::QueryInterface(const IID& riid, void** ppvObject)
{
}

ULONG DSH::Audio::System::AddRef()
{
}

ULONG DSH::Audio::System::Release()
{
}

void DSH::Audio::System::Update()
{
}

HRESULT DSH::Audio::System::CreateSound(const std::filesystem::path& path, ChannelGroupType group, bool isLoop,
	ISound** ppSound)
{
}

HRESULT DSH::Audio::System::Pause()
{
}

HRESULT DSH::Audio::System::Pause(ChannelGroupType group)
{
}

HRESULT DSH::Audio::System::Resume()
{
}

HRESULT DSH::Audio::System::Resume(ChannelGroupType group)
{
}

HRESULT DSH::Audio::System::Stop()
{
}

HRESULT DSH::Audio::System::Stop(ChannelGroupType group)
{
}

HRESULT DSH::Audio::System::SetVolume(float volume)
{
}

HRESULT DSH::Audio::System::SetVolume(ChannelGroupType group, float volume)
{
}

HRESULT DSH::Audio::System::Mute()
{
}

HRESULT DSH::Audio::System::Mute(ChannelGroupType group)
{
}

HRESULT DSH::Audio::System::Unmute()
{
}

HRESULT DSH::Audio::System::Unmute(ChannelGroupType group)
{
}
