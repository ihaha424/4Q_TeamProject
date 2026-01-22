#include "pch.h"
#include "StaticMesh.h"
#include "GEGraphicsManager.h"

void Engine::Component::StaticMesh::Initialize(const Modules& modules)
{
	Mesh::Initialize(modules);
	GE::MESH_RENDERER_DESC desc
	{
		.filePath = _filePath.c_str(),
		.type = GE::MESH_RENDERER_DESC::Type::Static
	};

	auto renderSystem = _graphicsManager->GetRenderSystem();
	renderSystem->CreateMeshRenderer(&_geMeshRenderer, &desc);
}

