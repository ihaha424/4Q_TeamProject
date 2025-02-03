#pragma once

namespace DSH::Logger
{
	namespace Target
	{
		struct Target;
	}

	class Stream final : public IStream
	{
	public:
		Stream(const std::vector<Target::Target*>* targets, const LogLevel* leastLogLevel, const std::unordered_map<LogLevel, bool>* loggableMap);

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		IStream& operator<<(LogLevel logLevel) override;
		IStream& operator<<(ConstCharPointer message) override;
		IStream& operator<<(StringView message) override;
		void Log(LogLevel logLevel, ConstCharPointer message) override;
		void Log(LogLevel logLevel, StringView message) override;

		void Flush() override;
		void FlushAsync() override;

	private:
		void SetLogLevel(LogLevel logLevel);
		void CheckBufferSize();
		static String GetTimeString();
		void WriteToTarget(OStringStream* source) const;
		OStringStream* FlipBuffer();

		ULONG _referenceCount;

		LogLevel _logLevel;
		std::array<OStringStream, 2> _buffers;
		DWORD _bufferIndex;
		OStringStream* _currentBuffer;
		std::future<void> _flushResult;

		const std::vector<Target::Target*>* _targets;
		const LogLevel* _leastLogLevel;
		const std::unordered_map<LogLevel, bool>* _loggableMap;
	};
}
