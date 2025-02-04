#include "pch.h"
#include "Camera.h"
#include "GEGraphicsManager.h"

Engine::Component::Camera::Camera(const float nearZ, const float farZ, const Math::Size size, const float fov) :
	_nearZ(nearZ), _farZ(farZ),	_size(size), _fov(fov), _graphicsManager(nullptr), _geCamera(nullptr)
{
}

void Engine::Component::Camera::SetName(std::wstring&& name)
{
	_name = std::move(name);
}

void Engine::Component::Camera::Initialize(const Modules& modules)
{
	Component::Initialize(modules);
	_graphicsManager = modules.graphicsManager;

	auto* cameraSystem = _graphicsManager->GetCameraSystem();
	cameraSystem->CreateCamera(&_geCamera);
	_geCamera->SetPerspective(_nearZ, _farZ, static_cast<float>(_size.cx) / static_cast<float>(_size.cy), _fov);
	//_geCamera->SetPosition(0.f, 50.f, -150.f); // TODO: Get position from object.
	_geCamera->SetRotationFromAngle(0.f, 0.f, 0.f);
}

void Engine::Component::Camera::Attach()
{
	Component::Attach();
	auto* cameraSystem = _graphicsManager->GetCameraSystem();
	cameraSystem->RegisterCamera(_name.c_str(), _geCamera);

	//_graphicsManager->RegisterCamera(_name, _camera);
}

void Engine::Component::Camera::Detach()
{
	Component::Detach();
	auto* cameraSystem = _graphicsManager->GetCameraSystem();
	cameraSystem->UnRegisterCamera(_name.c_str());

	//_graphicsManager->UnregisterCamera(_name);
}

void Engine::Component::Camera::Finalize()
{
	Component::Finalize();

	Utility::SafeRelease()(&_geCamera);
	//_camera->Finalize();
}

void Engine::Component::Camera::Activate() const
{
	// _graphicsManager->SetActiveCamera(_name);
	auto* cameraSystem = _graphicsManager->GetCameraSystem();
	cameraSystem->SetCurrentCamera(_name.c_str());
}

Engine::Math::Matrix Engine::Component::Camera::GetCameraMatrix() const
{
	return _geCamera->GetCameraMatrix();
}

void Engine::Component::Camera::SetPosition(const Math::Vector3 position) const
{
	_geCamera->SetPosition(position.x, position.y, position.z);
}

void Engine::Component::Camera::SetRotation(const Math::Vector3 rotation) const
{
	_geCamera->SetRotationFromAngle(rotation.x, rotation.y, rotation.z);
}

void Engine::Component::Camera::SetParent(Math::Matrix* matrix) const
{
	_geCamera->SetParent(matrix);
}

void Engine::Component::Camera::Rotate(Math::Vector3 rotation)
{
	// TODO: Implement this function.
}
