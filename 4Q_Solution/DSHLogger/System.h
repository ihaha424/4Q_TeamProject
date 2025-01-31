#pragma once

namespace DSH::Logger
{
	class Target;

	class System final : public ISystem
	{
	public:
		System();
		System(const System& other) = default;
		System(System&& other) noexcept = default;
		System& operator=(const System& other) = default;
		System& operator=(System&& other) noexcept = default;
		~System() override;

		HRESULT QueryInterface(const IID& riid, void** ppvObject) override;
		ULONG AddRef() override;
		ULONG Release() override;

		HRESULT CreateStream(IStream** ppStream) override;

		void EnableConsole() override;
		void EnableFile(std::filesystem::path path) override;

		void SetLeastLogLevel(LogLevel logLevel) override;
		void SetLoggable(LogLevel logLevel, bool loggable) override;

	private:
		ULONG _referenceCount;

		std::vector<Target*> _targets;

		LogLevel _leastLogLevel;
		std::unordered_map<LogLevel, bool> _loggableMap;
	};
}