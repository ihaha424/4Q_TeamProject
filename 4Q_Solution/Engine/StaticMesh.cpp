#include "pch.h"
#include "StaticMesh.h"

Engine::Component::StaticMesh::StaticMesh(std::filesystem::path filePath)
	: Mesh(std::move(filePath))
{
}
