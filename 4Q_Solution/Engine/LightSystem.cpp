#include "pch.h"
#include "LightSystem.h"

void Engine::Manager::GraphicsSystem::LightSystem::Initialize(GE::ILightSystem* lightSystem)
{
	assert(lightSystem != nullptr);
	assert(_lightSystem == nullptr);
	_lightSystem = lightSystem;
}

void Engine::Manager::GraphicsSystem::LightSystem::Finalize()
{
	Utility::SafeRelease()(&_lightSystem);
}

void Engine::Manager::GraphicsSystem::LightSystem::CreateLight(GE::ILight** outLight) const
{
	assert(outLight != nullptr);
	_lightSystem->CreateLight(outLight);
}

void Engine::Manager::GraphicsSystem::LightSystem::RegisterLight(GE::ILight* light) const
{
	assert(light != nullptr);
	_lightSystem->RegisterLight(light);
}

void Engine::Manager::GraphicsSystem::LightSystem::UnRegisterLight(GE::ILight* light) const
{
	assert(light != nullptr);
	_lightSystem->UnRegisterLight(light);
}
