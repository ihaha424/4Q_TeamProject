#include "pch.h"
#include "System.h"

#include "ConsoleTarget.h"
#include "FileTarget.h"
#include "Stream.h"

namespace DSH::Time
{
	class TickTimer;
}

DSH::Logger::System::System()
	: _referenceCount(1), _leastLogLevel(LogLevel::Trace),
	_loggableMap{
			std::pair<const LogLevel, bool>{LogLevel::Trace, true},
			std::pair<const LogLevel, bool>{LogLevel::Debug, true},
			std::pair<const LogLevel, bool>{LogLevel::Information, true},
			std::pair<const LogLevel, bool>{LogLevel::Warning, true},
			std::pair<const LogLevel, bool>{LogLevel::Error, true},
			std::pair<const LogLevel, bool>{LogLevel::Fatal, true}
		}
{
}

DSH::Logger::System::~System()
{
	for (const auto target : _targets) delete target;
	_targets.clear();
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
	Stream* pTickTimer = new Stream(&_targets, &_leastLogLevel, &_loggableMap);
	if (pTickTimer == nullptr) return E_OUTOFMEMORY;
	*ppStream = pTickTimer;
	return S_OK;
}

void DSH::Logger::System::EnableConsole()
{
	_targets.push_back(new Target::ConsoleTarget);
}

void DSH::Logger::System::EnableFile(const std::filesystem::path path)
{
	_targets.push_back(new Target::FileTarget(path));
}

void DSH::Logger::System::SetLeastLogLevel(const LogLevel logLevel)
{
	_leastLogLevel = logLevel;
}

void DSH::Logger::System::SetLoggable(const LogLevel logLevel, const bool loggable)
{
	_loggableMap.at(logLevel) = loggable;
}
