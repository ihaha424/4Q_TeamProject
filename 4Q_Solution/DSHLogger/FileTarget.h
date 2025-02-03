#pragma once
#include "Target.h"

namespace DSH::Logger::Target
{
	class FileTarget final : public Target
	{
	public:
		explicit FileTarget(const std::filesystem::path& path);
		FileTarget(const FileTarget& other);
		FileTarget(FileTarget&& other) noexcept = default;
		FileTarget& operator=(const FileTarget& other);
		FileTarget& operator=(FileTarget&& other) noexcept = default;
		~FileTarget() override;

		Target& operator<<(StringView description) override;

	private:
		std::filesystem::path _path;
		OFStream _fileStream;
	};
}
