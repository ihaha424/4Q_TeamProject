#include "pch.h"
#include "Mesh.h"
#include "GEGraphicsManager.h"

Engine::Component::Mesh::Mesh(std::filesystem::path filePath, Engine::Math::Matrix* matrix)
	: _filePath(std::move(filePath))
	, _geMatrix(matrix)
	, _geMeshRenderer(nullptr)
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

void Engine::Component::Mesh::SetRenderLayer(const unsigned int layer)
{
	_geMeshRenderer->SetRenderLayer(layer);
}
