#include "pch.h"
#include "SoundComponent.h"

void Engine::Component::Sound::SetPath(const std::filesystem::path& path)
{
	_path = path;
}

void Engine::Component::Sound::Finalize()
{
	Component::Finalize();
	Utility::SafeRelease()(&_sound);
}

void Engine::Component::Sound::Play() const
{
	Utility::ThrowIfFailed()(_sound->Play());
}

void Engine::Component::Sound::Stop() const
{
	Utility::ThrowIfFailed()(_sound->Stop());
}

void Engine::Component::Sound::Pause() const
{
	Utility::ThrowIfFailed()(_sound->Pause());
}

void Engine::Component::Sound::Resume() const
{
	Utility::ThrowIfFailed()(_sound->Resume());
}

void Engine::Component::Sound::Mute() const
{
	Utility::ThrowIfFailed()(_sound->Mute());
}

void Engine::Component::Sound::Unmute() const
{
	Utility::ThrowIfFailed()(_sound->Unmute());
}

bool Engine::Component::Sound::IsPlaying() const
{
	return _sound->IsPlaying();
}

bool Engine::Component::Sound::IsPaused() const
{
	return _sound->IsPaused();
}

bool Engine::Component::Sound::IsMuted() const
{
	return _sound->IsMuted();
}

void Engine::Component::Sound::FadeIn(const float duration) const
{
	Utility::ThrowIfFailed()(_sound->FadeIn(duration));
}

void Engine::Component::Sound::FadeOut(const float duration) const
{
	Utility::ThrowIfFailed()(_sound->FadeOut(duration));
}

void Engine::Component::Sound::SetVolume(const float volume) const
{
	Utility::ThrowIfFailed()(_sound->SetVolume(volume));
}

float Engine::Component::Sound::GetVolume() const
{
	return _sound->GetVolume();
}
