#include "pch.h"
#include "GEGraphicsCamera.h"

void Engine::GEGraphics::Camera::Setup(GE::ICamera* camera)
{
	_camera = camera;
}

void Engine::GEGraphics::Camera::Finalize()
{
	Utility::SafeRelease()(&_camera);
}

void Engine::GEGraphics::Camera::SetPerspective(const float nearZ, const float farZ, const float aspectRatio, const float fov)
{
	_camera->SetPerspective(nearZ, farZ, aspectRatio, fov);
}

void Engine::GEGraphics::Camera::SetPosition(const float x, const float y, const float z)
{
	_camera->SetPosition(x, y, z);
}

GE::ICamera* Engine::GEGraphics::Camera::Get() const
{
	return _camera;
}
