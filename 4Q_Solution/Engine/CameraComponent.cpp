#include "pch.h"
#include "CameraComponent.h"
#include "GEGraphicsManager.h"

Engine::Component::CameraComponent::CameraComponent(const float nearZ, const float farZ, const Math::Size size, const float fov) :
	_nearZ(nearZ), _farZ(farZ),	_size(size), _fov(fov), _graphicsManager(nullptr), _camera(nullptr)
{
}

void Engine::Component::CameraComponent::SetName(std::wstring&& name)
{
	_name = std::move(name);
}

void Engine::Component::CameraComponent::Initialize(const Modules& modules)
{
	Component::Initialize(modules);
	_graphicsManager = modules.graphicsManager;
	_graphicsManager->CreateCamera(&_camera);
	_camera->SetPerspective(_nearZ, _farZ, static_cast<float>(_size.cx) / static_cast<float>(_size.cy), _fov);
	_camera->SetPosition(0.f, 50.f, -150.f); // TODO: Get position from object.
	_camera->SetRotationFromAngle(0.f, 0.f, 0.f);
}

void Engine::Component::CameraComponent::Attach()
{
	Component::Attach();
	_graphicsManager->RegisterCamera(_name, _camera);
}

void Engine::Component::CameraComponent::Detach()
{
	Component::Detach();
	_graphicsManager->UnregisterCamera(_name);
}

void Engine::Component::CameraComponent::Finalize()
{
	Component::Finalize();
	_camera->Finalize();
}

void Engine::Component::CameraComponent::Activate() const
{
	_graphicsManager->SetActiveCamera(_name);
}

void Engine::Component::CameraComponent::SetPosition(const Math::Vector3 position) const
{
	_camera->SetPosition(position.x, position.y, position.z);
}

void Engine::Component::CameraComponent::SetRotation(const Math::Vector3 rotation) const
{
	_camera->SetRotationFromAngle(rotation.x, rotation.y, rotation.z);
}

void Engine::Component::CameraComponent::Rotate(Math::Vector3 rotation)
{
	// TODO: Implement this function.
}
