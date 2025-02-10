#include "pch.h"
#include "BackgroundMusicComponent.h"
#include "DSHAudioManager.h"

void Engine::Component::BackgroundMusic::Initialize(const Modules& modules)
{
	Sound::Initialize(modules);
	modules.audioManager->CreateSound(_path, true, true, &_sound);
}
