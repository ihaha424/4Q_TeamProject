#include "pch.h"
#include "SkeletalMesh.h"

Engine::Component::SkeletalMesh::SkeletalMesh(std::filesystem::path filePath)
	: Mesh(std::move(filePath))
{
}