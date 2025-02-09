#include "pch.h"
#include "Live.h"

Live::Live(std::filesystem::path&& meshPath)
{
	_meshPath = std::forward<std::filesystem::path>(meshPath);
}
