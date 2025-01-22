#include "pch.h"
#include "StaticMesh.h"
#include "GEGraphicsManager.h"

Engine::Component::StaticMesh::StaticMesh(std::filesystem::path filePath, Engine::Math::Matrix* matrix)
	: Mesh(std::move(filePath), matrix)
{
}

void Engine::Component::StaticMesh::Initialize()
{
	GE::MESH_RENDERER_DESC desc
	{
		.filePath = _filePath.c_str(),
		.type = GE::MESH_RENDERER_DESC::Type::Static
	};

	auto renderSystem = _graphicsManager->GetRenderSystem();
	renderSystem->CreateMeshRenderer(&_geMeshRenderer, &desc);
}