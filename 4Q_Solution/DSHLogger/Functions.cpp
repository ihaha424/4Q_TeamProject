#include "pch.h"
#include "Functions.h"

HRESULT DSH::Logger::CreateSystem::operator()(ISystem** ppSystem) const
{
	if (ppSystem == nullptr) return E_INVALIDARG;
	//System* pSystem = new System();
	//if (pSystem == nullptr) return E_OUTOFMEMORY;
	//*ppSystem = pSystem;
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
