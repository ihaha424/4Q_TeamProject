#pragma once

namespace DSH::Logger::Target
{
	struct Target
	{
		Target() = default;
		Target(const Target& other) = default;
		Target(Target&& other) noexcept = default;
		Target& operator=(const Target& other) = default;
		Target& operator=(Target&& other) noexcept = default;
		virtual ~Target() = default;

		virtual Target& operator<<(StringView description) = 0;
	};
}
