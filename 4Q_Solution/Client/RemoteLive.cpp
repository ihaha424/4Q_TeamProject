#include "pch.h"
#include "RemoteLive.h"

RemoteLive::RemoteLive(std::filesystem::path&& meshPath)
{
	_meshPath = std::forward<std::filesystem::path>(meshPath);
}
