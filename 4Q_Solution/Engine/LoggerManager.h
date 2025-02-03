#pragma once

namespace Engine::Logger
{
	struct IManager
	{
		IManager() = default;
		IManager(const IManager& other) = default;
		IManager(IManager&& other) noexcept = default;
		IManager& operator=(const IManager& other) = default;
		IManager& operator=(IManager&& other) noexcept = default;
		virtual ~IManager() = default;

		virtual void EnableConsole() = 0;
		virtual void EnableFile(const std::filesystem::path& path) = 0;

		virtual void Log(LogLevel logLevel, const std::wstring& message) = 0;
	};

	struct Manager : IManager
	{
		virtual void Initialize(const std::filesystem::path& dumpPath) = 0;
		virtual void Flush() = 0;
		virtual void Finalize() = 0;
	};
}
