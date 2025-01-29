#include "pch.h"
#include "SkeletalMesh.h"
#include "GEGraphicsManager.h"

void Engine::Component::SkeletalMesh::Initialize(const Modules& modules)
{
	Mesh::Initialize(modules);
	GE::MESH_RENDERER_DESC desc
	{
		.filePath = _filePath.c_str(),
		.type = GE::MESH_RENDERER_DESC::Type::Skeletal
	};

	auto renderSystem = _graphicsManager->GetRenderSystem();
	renderSystem->CreateMeshRenderer(&_geMeshRenderer, &desc);
}