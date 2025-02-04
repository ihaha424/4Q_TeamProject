#include "pch.h"
#include "CameraSystem.h"
#include "Camera.h"
#include "includes/ICamera.h"

void CameraSystem::SetCurrentCamera(const wchar_t* name)
{
	if (_cameras.find(name) == _cameras.end())
	{
		ASSERT(false, L"No cameras were found with that name.");
		return;
	}

	_pCurrentCamera = _cameras[name];
}

void CameraSystem::Release()
{
	delete this;
}

void CameraSystem::CreateCamera(GE::ICamera** ppCamera)
{
	(*ppCamera) = new Camera;
}

void CameraSystem::Update()
{
	if (nullptr == _pCurrentCamera)
	{
		ASSERT(false, L"No cameras are currently set up.");
		return;
	}

	_pCurrentCamera->Update();
}

void CameraSystem::RegisterCamera(const wchar_t* name, GE::ICamera* pCaemra)
{
	if (_cameras.find(name) != _cameras.end())
	{
		ASSERT(false, L"Already registered camera.");
		return;
	}

	_cameras[name] = static_cast<Camera*>(pCaemra);
}

void CameraSystem::UnRegisterCamera(const wchar_t* name)
{
	if (_cameras.find(name) == _cameras.end())
	{
		ASSERT(false, L"Unregistered camera.");
		return;
	}

	_cameras.erase(name);
}