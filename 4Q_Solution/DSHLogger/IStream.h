#pragma once

namespace DSH::Logger
{
	EXTERN_C const IID IID_IStream;

	EXTERN_C MIDL_INTERFACE("becb533a-5e36-4b18-8aa7-eb5fdd0715d9")
		IStream : IUnknown
	{
		IStream() = default;
		IStream(const IStream& other) = default;
		IStream(IStream&& other) noexcept = default;
		IStream& operator=(const IStream& other) = default;
		IStream& operator=(IStream&& other) noexcept = default;
		virtual ~IStream() = default;

		virtual IStream& STDMETHODCALLTYPE operator<<(
			/* [annotation][in] */
			_In_ LogLevel logLevel) = 0;

		virtual IStream& STDMETHODCALLTYPE operator<<(
			/* [annotation][in] */
			_In_ ConstCharPointer message) = 0;

		virtual IStream& STDMETHODCALLTYPE operator<<(
			/* [annotation][in] */
			_In_ StringView message) = 0;

		virtual void STDMETHODCALLTYPE Log(
			/* [annotation][in] */
			_In_ LogLevel logLevel,
			/* [annotation][in] */
			_In_ ConstCharPointer message) = 0;

		virtual void STDMETHODCALLTYPE Log(
			/* [annotation][in] */
			_In_ LogLevel logLevel,
			/* [annotation][in] */
			_In_ StringView message) = 0;

		virtual void STDMETHODCALLTYPE Flush() = 0;

		virtual void STDMETHODCALLTYPE FlushAsync() = 0;
	};
}
