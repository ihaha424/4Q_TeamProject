#include "pch.h"
#include "ShadowCamera.h"
#include "GEGraphicsManager.h"

Engine::Component::ShadowCamera::ShadowCamera(float nearZ, float farZ, Math::Size size, float fov)
	: Engine::Component::Camera(nearZ, farZ, size, fov)
{
}

void Engine::Component::ShadowCamera::Activate() const
{
	auto* cameraSystem = _graphicsManager->GetCameraSystem();
	cameraSystem->SetShadowCamera(_name.c_str());
}
