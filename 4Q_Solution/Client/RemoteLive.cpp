#include "pch.h"
#include "RemoteLive.h"

RemoteLive::RemoteLive(std::filesystem::path&& meshPath)
{
	_meshPath = std::forward<std::filesystem::path>(meshPath);
}

void RemoteLive::PostInitialize(const Engine::Modules& modules)
{
	Remote::PostInitialize(modules);
	_skeletalMesh->SetZWrite(true);
}