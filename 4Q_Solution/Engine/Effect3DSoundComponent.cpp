#include "pch.h"
#include "Effect3DSoundComponent.h"
#include "DSHAudioManager.h"

void Engine::Component::Effect3DSound::Initialize(const Modules& modules)
{
	Sound::Initialize(modules);
	modules.audioManager->CreateSound(_path, &_sound3D);
	_sound = _sound3D;
}

void Engine::Component::Effect3DSound::SetPosition(const Math::Vector3& position) const
{
	Utility::ThrowIfFailed()(_sound3D->SetPosition(position));
}

void Engine::Component::Effect3DSound::SetVelocity(const Math::Vector3& velocity) const
{
	Utility::ThrowIfFailed()(_sound3D->SetVelocity(velocity));
}

void Engine::Component::Effect3DSound::SetMaxDistance(const float maxDistance) const
{
	Utility::ThrowIfFailed()(_sound3D->SetMaxDistance(maxDistance));
}

void Engine::Component::Effect3DSound::SetMinDistance(const float minDistance) const
{
	Utility::ThrowIfFailed()(_sound3D->SetMinDistance(minDistance));
}


