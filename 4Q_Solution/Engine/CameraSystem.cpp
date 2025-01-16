#include "pch.h"
#include "CameraSystem.h"

void Engine::Manager::GraphicsSystem::CameraSystem::Initialize(GE::ICameraSystem* cameraSystem)
{
	assert(cameraSystem != nullptr);
	assert(_cameraSystem == nullptr);
	_cameraSystem = cameraSystem;
}

void Engine::Manager::GraphicsSystem::CameraSystem::Update() const
{
	assert(_cameraSystem != nullptr);
	_cameraSystem->Update();
}

void Engine::Manager::GraphicsSystem::CameraSystem::Finalize()
{
	Utility::SafeRelease()(&_cameraSystem);
}


void Engine::Manager::GraphicsSystem::CameraSystem::CreateCamera(GE::ICamera** camera) const
{
	assert(_cameraSystem != nullptr);
	_cameraSystem->CreateCamera(camera);
}

void Engine::Manager::GraphicsSystem::CameraSystem::RegisterCamera(const std::wstring_view name, GE::ICamera* camera) const
{
	assert(_cameraSystem != nullptr);
	_cameraSystem->RegisterCamera(name.data(), camera);
}

void Engine::Manager::GraphicsSystem::CameraSystem::Unregister(const std::wstring_view name) const
{
	assert(_cameraSystem != nullptr);
	_cameraSystem->UnRegisterCamera(name.data());
}

void Engine::Manager::GraphicsSystem::CameraSystem::SetCurrentCamera(const std::wstring_view name) const
{
	assert(_cameraSystem != nullptr);
	_cameraSystem->SetCurrentCamera(name.data());
}
