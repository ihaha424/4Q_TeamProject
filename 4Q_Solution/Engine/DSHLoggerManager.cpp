#include "pch.h"
#include "DSHLoggerManager.h"

Engine::DSHLogger::Manager::Manager() :
	_system(nullptr), _stream(nullptr),
	_logLevelMap{
		std::pair<const Logger::LogLevel, DSH::Logger::LogLevel>{ Logger::LogLevel::Trace, DSH::Logger::LogLevel::Trace },
		std::pair<const Logger::LogLevel, DSH::Logger::LogLevel>{ Logger::LogLevel::Debug, DSH::Logger::LogLevel::Debug },
		std::pair<const Logger::LogLevel, DSH::Logger::LogLevel>{ Logger::LogLevel::Information, DSH::Logger::LogLevel::Information },
		std::pair<const Logger::LogLevel, DSH::Logger::LogLevel>{ Logger::LogLevel::Warning, DSH::Logger::LogLevel::Warning },
		std::pair<const Logger::LogLevel, DSH::Logger::LogLevel>{ Logger::LogLevel::Error, DSH::Logger::LogLevel::Error },
		std::pair<const Logger::LogLevel, DSH::Logger::LogLevel>{ Logger::LogLevel::Fatal, DSH::Logger::LogLevel::Fatal }
	}
{
}

void Engine::DSHLogger::Manager::Initialize(const std::filesystem::path& dumpPath)
{
	static std::filesystem::path path = dumpPath;

	if (!exists(path))	create_directories(path);

	SetUnhandledExceptionFilter([](EXCEPTION_POINTERS* pointers)->LONG { return DSH::Logger::RecordDump(path, MiniDumpNormal)(pointers); });

	constexpr Utility::ThrowIfFailed thrower;

	thrower(DSH::Logger::CreateSystem()(&_system));
	thrower(_system->CreateStream(&_stream));
}

void Engine::DSHLogger::Manager::Flush()
{
	_stream->FlushAsync();
}

void Engine::DSHLogger::Manager::Finalize()
{
	constexpr Utility::SafeRelease releaser;
	releaser(&_stream);
	releaser(&_system);
}

void Engine::DSHLogger::Manager::EnableConsole()
{
	_system->EnableConsole();
}

void Engine::DSHLogger::Manager::EnableFile(const std::filesystem::path& path)
{
	_system->EnableFile(path);
}

void Engine::DSHLogger::Manager::Log(const Logger::LogLevel logLevel, const std::wstring& message)
{
	_stream->Log(_logLevelMap.at(logLevel), message);
}
