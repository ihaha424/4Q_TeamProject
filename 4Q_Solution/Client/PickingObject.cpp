#include "pch.h"
#include "PickingObject.h"

PickingObject::PickingObject(std::filesystem::path&& meshPath)
	: _staticMesh(nullptr), _meshPath(std::forward<std::filesystem::path>(meshPath))
	, _rigidStatc{ nullptr }
{
}

void PickingObject::Prepare(Engine::Content::Factory::Component* componentFactory)
{
}

void PickingObject::SetIsPublic(bool isPublic)
{
}

void PickingObject::SetisDynamic(bool isDynamic)
{
}

void PickingObject::SetHasMesh(bool hasMesh)
{
}

void PickingObject::SetBoxScale(Engine::Math::Vector3 boxScale)
{
}

void PickingObject::DisposeComponents()
{
}

void PickingObject::PreInitialize(const Engine::Modules& modules)
{
}
