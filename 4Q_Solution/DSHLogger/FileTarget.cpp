#include "pch.h"
#include "FileTarget.h"

DSH::Logger::Target::FileTarget::FileTarget(const std::filesystem::path& path) :
	_path(path), _fileStream(path, std::ios::out | std::ios::app)
{
	if (!_fileStream.is_open()) throw std::runtime_error("Failed to open file.");
}

DSH::Logger::Target::FileTarget::FileTarget(const FileTarget& other) :
	_path(other._path), _fileStream(other._path, std::ios::out | std::ios::app)
{;
}

DSH::Logger::Target::FileTarget& DSH::Logger::Target::FileTarget::operator=(const FileTarget& other)
{
	if (this == &other) return *this;
	_path = other._path;
	_fileStream = OFStream(other._path, std::ios::out | std::ios::app);
	return *this;
}

DSH::Logger::Target::FileTarget::~FileTarget()
{
	_fileStream.close();
}

DSH::Logger::Target::Target& DSH::Logger::Target::FileTarget::operator<<(const StringView description)
{
	_fileStream << description;
	return *this;
}
