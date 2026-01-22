#pragma once

namespace Engine::DSHLogger
{
	class Manager final : public Logger::Manager
	{
	public:
		Manager();

		void Initialize(const std::filesystem::path& dumpPath) override;
		void Flush() override;
		void Finalize() override;

		void EnableConsole() override;
		void EnableFile(const std::filesystem::path& path) override;

		void Log(Logger::LogLevel logLevel, const std::wstring& message) override;

	private:
		DSH::Logger::ISystem* _system;
		DSH::Logger::IStream* _stream;

		std::unordered_map<Logger::LogLevel, DSH::Logger::LogLevel> _logLevelMap;
	};
}
