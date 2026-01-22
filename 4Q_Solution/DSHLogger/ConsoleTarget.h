#pragma once
#include "Target.h"

namespace DSH::Logger::Target
{
	class ConsoleTarget final : public Target
	{
	public:
		ConsoleTarget();
		ConsoleTarget(const ConsoleTarget& other) = default;
		ConsoleTarget(ConsoleTarget&& other) noexcept = default;
		ConsoleTarget& operator=(const ConsoleTarget& other) = default;
		ConsoleTarget& operator=(ConsoleTarget&& other) noexcept = default;
		~ConsoleTarget() override;

		Target& operator<<(StringView description) override;
	};
}
