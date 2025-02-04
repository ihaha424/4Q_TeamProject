#pragma once

namespace DSH::Logger
{
#ifdef _UNICODE
	using ConstCharPointer = const wchar_t*;
	using String = std::wstring;
	using StringView = std::wstring_view;
	using IStringStream = std::wistringstream;
	using OStringStream = std::wostringstream;
	using OStream = std::wostream;
	using OFStream = std::wofstream;
#define DEFAULT_CONSOLE std::wcout
#define EMPTY L""
#define SPACE L' '
#define CARRIAGE_RETURN L'\n' 
#define TIME_FORMAT L"[{0:%c}]"
#define LITERAL(str) L##str
#else
	using ConstCharPointer = const char*;
	using String = std::string;
	using StringView = std::string_view;
	using IStringStream = std::istringstream;
	using OStringStream = std::ostringstream;
	using OStream = std::ostream;
	using OFStream = std::ofstream;
#define DEFAULT_CONSOLE std::cout
#define EMPTY ""
#define SPACE ' '
#define CARRIAGE_RETURN '\n' 
#define TIME_FORMAT "[{0:%c}]"
#define LITERAL(str) ##str
#endif

	constexpr std::size_t STDMETHODCALLTYPE operator""_KB(
		/* [annotation][in] */
		_In_ const ULONGLONG value)
	{
		return value * 1024;
	}

	constexpr std::size_t STDMETHODCALLTYPE operator""_MB(
		/* [annotation][in] */
		_In_ const ULONGLONG value)
	{
		return operator""_KB(value) * 1024;
	}

	constexpr std::size_t STDMETHODCALLTYPE operator""_GB(
		/* [annotation][in] */
		_In_ const ULONGLONG value)
	{
		return operator""_MB(value) * 1024;
	}

	constexpr std::size_t STDMETHODCALLTYPE operator""_TB(
		/* [annotation][in] */
		_In_ const ULONGLONG value)
	{
		return operator""_GB(value) * 1024;
	}

	enum class LogLevel : unsigned char
	{
		Trace,
		Debug,
		Information,
		Warning,
		Error,
		Fatal
	};
}
