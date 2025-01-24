#include "pch.h"
#include "SkeletalMesh.h"
#include "GEGraphicsManager.h"

Engine::Component::SkeletalMesh::SkeletalMesh(std::filesystem::path filePath, Engine::Math::Matrix* matrix)
	: Mesh(std::move(filePath), matrix)
{
}

void Engine::Component::SkeletalMesh::Initialize()
{
	GE::MESH_RENDERER_DESC desc
	{
		.filePath = _filePath.c_str(),
		.type = GE::MESH_RENDERER_DESC::Type::Skeletal
	};

	auto renderSystem = _graphicsManager->GetRenderSystem();
	renderSystem->CreateMeshRenderer(&_geMeshRenderer, &desc);
}