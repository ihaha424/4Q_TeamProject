#include "pch.h"
#include "RemoteRay.h"

RemoteRay::RemoteRay(std::filesystem::path&& meshPath)
{
	_meshPath = std::forward<std::filesystem::path>(meshPath);
}
