#include "pch.h"
#include "Stream.h"

#include "Functions.h"
#include "Target.h"

DSH::Logger::Stream::Stream(const std::vector<Target::Target*>* targets,
                            const LogLevel* leastLogLevel, const std::unordered_map<LogLevel, bool>* loggableMap) :
	_referenceCount(1),
	_logLevel(LogLevel::Trace),
	_bufferIndex(0),
	_currentBuffer(&_buffers[_bufferIndex]),
	_targets(targets), _leastLogLevel(leastLogLevel), _loggableMap(loggableMap)
{
	std::ranges::for_each(_buffers, [](auto& buffer) {buffer.str().reserve(1_GB); });
}

HRESULT DSH::Logger::Stream::QueryInterface(const IID& riid, void** ppvObject)
{
	if (ppvObject == nullptr) return E_INVALIDARG;
	if (riid != IID_IStream &&
		riid != IID_IUnknown) return E_NOINTERFACE;
	*ppvObject = this;
	return S_OK;
}

ULONG DSH::Logger::Stream::AddRef()
{
	return InterlockedIncrement(&_referenceCount);
}

ULONG DSH::Logger::Stream::Release()
{
	const ULONG newRefCount = InterlockedDecrement(&_referenceCount);
	if (newRefCount == 0) delete this;
	return newRefCount;
}

DSH::Logger::IStream& DSH::Logger::Stream::operator<<(const LogLevel logLevel)
{
	SetLogLevel(logLevel);
	return *this;
}

DSH::Logger::IStream& DSH::Logger::Stream::operator<<(const ConstCharPointer message)
{
	Log(_logLevel, message);
	return *this;
}

DSH::Logger::IStream& DSH::Logger::Stream::operator<<(const StringView message)
{
	Log(_logLevel, message);
	return *this;
}

void DSH::Logger::Stream::Log(const LogLevel logLevel, const ConstCharPointer message)
{
	if (logLevel < *_leastLogLevel || !_loggableMap->at(logLevel)) return;
	*_currentBuffer << GetTimeString() << SPACE << LogLevelToString()(logLevel) << SPACE << message << CARRIAGE_RETURN;
}

void DSH::Logger::Stream::Log(const LogLevel logLevel, const StringView message)
{
	Log(logLevel, message.data());
}

void DSH::Logger::Stream::Flush()
{
	if (_flushResult.valid()) _flushResult.get();
	OStringStream* source = FlipBuffer();
	WriteToTarget(source);
}

void DSH::Logger::Stream::FlushAsync()
{
	if (_flushResult.valid()) _flushResult.get();
	OStringStream* source = FlipBuffer();
	_flushResult = std::async(std::launch::async, &Stream::WriteToTarget, this, source);

}

void DSH::Logger::Stream::SetLogLevel(const LogLevel logLevel)
{
	_logLevel = logLevel;
}

void DSH::Logger::Stream::CheckBufferSize()
{
	if (_currentBuffer->str().size() > 1_GB) Flush();
}

DSH::Logger::String DSH::Logger::Stream::GetTimeString()
{
	std::chrono::time_point<std::chrono::system_clock> time = std::chrono::system_clock::now();
	return std::format(TIME_FORMAT, time);
}

void DSH::Logger::Stream::WriteToTarget(OStringStream* source) const
{
	for (const auto& target : *_targets)
	{
		(*target) << source->str();
	}
	source->str(EMPTY);
}

DSH::Logger::OStringStream* DSH::Logger::Stream::FlipBuffer()
{
	OStringStream* previousBuffer = _currentBuffer;
	_bufferIndex = ++_bufferIndex % 2;
	_currentBuffer = &_buffers[_bufferIndex];
	return previousBuffer;
}
