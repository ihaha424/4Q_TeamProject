#include "pch.h"
#include "ConsoleTarget.h"

DSH::Logger::Target::ConsoleTarget::ConsoleTarget()
{
	AllocConsole();
	FILE* traceConsoleStream;
	freopen_s(&traceConsoleStream, "CONOUT$", "w", stdout);
}

DSH::Logger::Target::ConsoleTarget::~ConsoleTarget()
{
	FreeConsole();
}

DSH::Logger::Target::Target& DSH::Logger::Target::ConsoleTarget::operator<<(const StringView description)
{
	DEFAULT_CONSOLE << description;
	return *this;
}
