#include "pch.h"
#include "Mesh.h"
#include "GEGraphicsManager.h"

Engine::Component::Mesh::Mesh(std::filesystem::path filePath, Engine::Math::Matrix* matrix)
	: _filePath(std::move(filePath))
	, _geMatrix(matrix)
	, _geMeshRenderer(nullptr)
	, _layer(0)
{
}

void Engine::Component::Mesh::Attach()
{
	Component::Attach();
	_graphicsManager->GetRenderSystem()->RegisterRenderQueue(_layer, _geMeshRenderer, _geMatrix);
}

void Engine::Component::Mesh::Detach()
{
	Component::Detach();
	_graphicsManager->GetRenderSystem()->UnRegisterRenderQueue(_layer, _geMeshRenderer);
}

void Engine::Component::Mesh::Finalize()
{
	_geMeshRenderer->Release();
}
