#pragma once

namespace DSH::Logger
{
	EXTERN_C struct DSH_LOGGER_LIBRARY_API CreateSystem
	{
		HRESULT STDMETHODCALLTYPE operator()(
			/* [annotation][out] */
			_Out_ ISystem** ppSystem) const;
	};

	EXTERN_C struct DSH_LOGGER_LIBRARY_API LogLevelToString
	{
		String STDMETHODCALLTYPE operator()(
			/* [annotation][in] */
			_In_ LogLevel logLevel) const;
	};
}
