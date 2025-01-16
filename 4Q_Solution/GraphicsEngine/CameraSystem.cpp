#include "pch.h"
#include "CameraSystem.h"
#include "Camera.h"
#include "includes/ICamera.h"

void CameraSystem::SetCurrentCamera(const wchar_t* name)
{
	if (_cameras.find(name) == _cameras.end())
	{
		ASSERT(false, L"해당 태그로 카메라를 찾을 수 없습니다.");
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
		ASSERT(false, L"설정된 카메라가 없습니다.");
		return;
	}

	_pCurrentCamera->Update();
}

void CameraSystem::RegisterCamera(const wchar_t* name, GE::ICamera* pCaemra)
{
	if (_cameras.find(name) != _cameras.end())
	{
		ASSERT(false, L"이미 등록된 카메라 입니다.");
		return;
	}

	_cameras[name] = static_cast<Camera*>(pCaemra);
}

void CameraSystem::UnRegisterCamera(const wchar_t* name)
{
	if (_cameras.find(name) == _cameras.end())
	{
		ASSERT(false, L"등록되지 않은 카메라 입니다.");
		return;
	}

	_cameras.erase(name);
}