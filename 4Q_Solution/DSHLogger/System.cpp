#include "pch.h"
#include "System.h"

#include "ConsoleTarget.h"

namespace DSH::Time
{
	class TickTimer;
}

DSH::Logger::System::System()
	: _referenceCount(1), _leastLogLevel(LogLevel::Trace),
	_loggableMap
	{
		std::pair<const LogLevel, bool>{LogLevel::Trace, true},
		std::pair<const LogLevel, bool>{LogLevel::Debug, true},
		std::pair<const LogLevel, bool>{LogLevel::Information, true},
		std::pair<const LogLevel, bool>{LogLevel::Warning, true},
		std::pair<const LogLevel, bool>{LogLevel::Error, true},
		std::pair<const LogLevel, bool>{LogLevel::Fatal, true}
	}
{
}

HRESULT DSH::Logger::System::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_ISystem &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Logger::System::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Logger::System::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

HRESULT DSH::Logger::System::CreateStream(IStream** ppStream)
{
	if (ppStream == nullptr) return E_INVALIDARG;
	//Stream* pTickTimer = new Stream();
	//if (pTickTimer == nullptr) return E_OUTOFMEMORY;
	//*ppStream = pTickTimer;
	return S_OK;
}

void DSH::Logger::System::EnableConsole()
{
	_targets.push_back(std::make_unique<Target::ConsoleTarget>());
}

void DSH::Logger::System::EnableFile(std::filesystem::path path)
{
	// TODO: Implement
}

void DSH::Logger::System::SetLeastLogLevel(const LogLevel logLevel)
{
	_leastLogLevel = logLevel;
}

void DSH::Logger::System::SetLoggable(const LogLevel logLevel, const bool loggable)
{
	_loggableMap[logLevel] = loggable;
}
