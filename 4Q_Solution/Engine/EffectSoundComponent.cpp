#include "pch.h"
#include "EffectSoundComponent.h"
#include "DSHAudioManager.h"

void Engine::Component::EffectSound::Initialize(const Modules& modules)
{
	Sound::Initialize(modules);
	modules.audioManager->CreateSound(_path, false, false, &_sound);
}