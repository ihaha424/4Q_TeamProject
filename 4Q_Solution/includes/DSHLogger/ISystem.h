#pragma once

namespace DSH::Logger
{
	struct IStream;

	EXTERN_C const IID IID_ISystem;

	EXTERN_C MIDL_INTERFACE("1b22c919-9992-4141-9777-a3762de242bb")
		ISystem : IUnknown
	{
		ISystem() = default;
		ISystem(const ISystem& other) = default;
		ISystem(ISystem&& other) noexcept = default;
		ISystem& operator=(const ISystem& other) = default;
		ISystem& operator=(ISystem&& other) noexcept = default;
		virtual ~ISystem() = default;

		virtual HRESULT STDMETHODCALLTYPE CreateStream(
			/* [annotation][out] */
			_Out_ IStream** ppStream) = 0;

		virtual void STDMETHODCALLTYPE EnableConsole() = 0;

		virtual void STDMETHODCALLTYPE EnableFile(
			/* [annotation][in] */
			_In_ std::filesystem::path path) = 0;

		virtual void STDMETHODCALLTYPE SetLeastLogLevel(
			/* [annotation][in] */
			_In_ LogLevel logLevel) = 0;

		virtual void STDMETHODCALLTYPE SetLoggable(
			/* [annotation][in] */
			_In_ LogLevel logLevel,
			/* [annotation][in] */
			_In_ bool loggable) = 0;
	};
}