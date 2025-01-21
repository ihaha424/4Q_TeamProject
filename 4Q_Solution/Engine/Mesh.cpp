#include "pch.h"
#include "Mesh.h"
#include "GEGraphicsManager.h"

Engine::Component::Mesh::Mesh(std::filesystem::path filePath)
	: _filePath(std::move(filePath))
	, _geMatrix(nullptr)
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
	_geMatrix->Release();
	_geMeshRenderer->Release();
}
