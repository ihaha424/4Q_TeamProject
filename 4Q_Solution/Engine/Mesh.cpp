#include "pch.h"
#include "Mesh.h"
#include "GEGraphicsManager.h"

Engine::Component::Mesh::Mesh() :
	_geMatrix(nullptr), _geMeshRenderer(nullptr)
{
}

void Engine::Component::Mesh::Attach()
{
	Component::Attach();
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

void Engine::Component::Mesh::SetRenderLayer(const unsigned int layer) const
{
	_geMeshRenderer->SetRenderLayer(layer);
}

void Engine::Component::Mesh::SetMatrix(Math::Matrix* matrix)
{
	_geMatrix = matrix;
}

void Engine::Component::Mesh::SetFilePath(const std::filesystem::path& filePath)
{
	_filePath = filePath;
}
