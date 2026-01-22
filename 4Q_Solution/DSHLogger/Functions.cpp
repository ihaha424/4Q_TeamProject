#include "pch.h"
#include "Functions.h"
#include "System.h"

HRESULT DSH::Logger::CreateSystem::operator()(ISystem** ppSystem) const
{
	if (ppSystem == nullptr) return E_INVALIDARG;
	System* pSystem = new System();
	if (pSystem == nullptr) return E_OUTOFMEMORY;
	*ppSystem = pSystem;
	return S_OK;
}

DSH::Logger::String DSH::Logger::LogLevelToString::operator()(const LogLevel logLevel) const
{
	String string;
	switch (logLevel)
	{
	case LogLevel::Trace:
	{
		string = LITERAL("[TRACE]");
	}
	break;
	case LogLevel::Debug:
	{
		string = LITERAL("[DEBUG]");
	}
	break;
	case LogLevel::Information:
	{
		string = LITERAL("[INFORMATION]");
	}
	break;
	case LogLevel::Warning:
	{
		string = LITERAL("[WARNING]");
	}
	break;
	case LogLevel::Error:
	{
		string = LITERAL("[ERROR]");
	}
	break;
	case LogLevel::Fatal:
	{
		string = LITERAL("[FATAL]");
	}
	break;
	}
	return string;
}

DSH::Logger::RecordDump::RecordDump(std::filesystem::path path, const MINIDUMP_TYPE type) : path(std::move(path)), type(type)
{
}

LONG DSH::Logger::RecordDump::operator()(EXCEPTION_POINTERS* exceptionPointers) const
{
	const HANDLE fileHandle = CreateFile(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);

	if (fileHandle == INVALID_HANDLE_VALUE) return HRESULT_FROM_WIN32(GetLastError());

	MINIDUMP_EXCEPTION_INFORMATION exceptInfo;
	exceptInfo.ThreadId = GetCurrentThreadId();
	exceptInfo.ClientPointers = FALSE;
	exceptInfo.ExceptionPointers = exceptionPointers;

	const BOOL result = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), fileHandle, type, exceptionPointers ? &exceptInfo : nullptr, nullptr, nullptr);
	CloseHandle(fileHandle);

	return result ? EXCEPTION_EXECUTE_HANDLER : HRESULT_FROM_WIN32(GetLastError());
}
