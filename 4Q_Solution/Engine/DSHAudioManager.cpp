#include "pch.h"
#include "DSHAudioManager.h"

void Engine::DSHAudio::Manager::Initialize()
{
	constexpr Utility::ThrowIfFailed thrower;
	thrower(DSH::Audio::CreateSystem()(&_system));
}

void Engine::DSHAudio::Manager::Update()
{
	_system->Update();
}

void Engine::DSHAudio::Manager::Finalize()
{
	constexpr Utility::SafeRelease releaser;
	releaser(&_system);
}

void Engine::DSHAudio::Manager::CreateSound(const std::filesystem::path& path, const bool isBackground, const bool isLoop,
	DSH::Audio::ISound** sound) const
{
	constexpr Utility::ThrowIfFailed thrower;
	thrower(_system->CreateSound(path, isBackground ? DSH::Audio::ChannelGroupType::Background : DSH::Audio::ChannelGroupType::Effect, isLoop, sound));
}

void Engine::DSHAudio::Manager::CreateSound(const std::filesystem::path& path, DSH::Audio::ISound3D** sound) const
{
	constexpr Utility::ThrowIfFailed thrower;
	thrower(_system->CreateSound(path, DSH::Audio::ChannelGroupType::Effect, false, sound));
}

void Engine::DSHAudio::Manager::CreateListener(DSH::Audio::IListener** listener) const
{
	constexpr Utility::ThrowIfFailed thrower;
	thrower(_system->CreateListener(listener));
}
