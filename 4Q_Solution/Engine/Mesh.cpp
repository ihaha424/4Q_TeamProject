#include "pch.h"
#include "Mesh.h"
#include "GEGraphicsManager.h"

Engine::Component::Mesh::Mesh()
	: _geMatrix(nullptr)
	, _geMeshRenderer(nullptr)
{
	_meshDescription.activeDraw = true;
	_meshDescription.activeShadow = true;
	_meshDescription.postEffectFlag = 0;
}

void Engine::Component::Mesh::Attach()
{
	Component::Attach();
	_geMeshRenderer->SetDesc(&_meshDescription);
	_graphicsManager->GetRenderSystem()->RegisterRenderQueue(_geMeshRenderer, _geMatrix);
}

void Engine::Component::Mesh::Detach()
{
	Component::Detach();
	_graphicsManager->GetRenderSystem()->UnRegisterRenderQueue(_geMeshRenderer);
}

void Engine::Component::Mesh::Finalize()
{
	_geMeshRenderer->Release();
}

void Engine::Component::Mesh::SetPostEffectFlag(const unsigned int flag)
{
	_meshDescription.postEffectFlag = flag;
	_geMeshRenderer->SetDesc(&_meshDescription);
}

void Engine::Component::Mesh::SetMatrix(Math::Matrix* matrix)
{
	_geMatrix = matrix;
}

void Engine::Component::Mesh::SetFilePath(const std::filesystem::path& filePath)
{
	_filePath = filePath;
}

void Engine::Component::Mesh::SetActiveDraw(bool isActive)
{
	_meshDescription.activeDraw = isActive;
	_geMeshRenderer->SetDesc(&_meshDescription);
}

void Engine::Component::Mesh::SetActiveShadow(bool isActive)
{
	_meshDescription.activeShadow = isActive;
	_geMeshRenderer->SetDesc(&_meshDescription);
}