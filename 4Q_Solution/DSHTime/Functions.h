#pragma once

namespace DSH::Time
{
	EXTERN_C struct DSH_TIME_LIBRARY_API CreateSystem
	{
		HRESULT STDMETHODCALLTYPE operator()(
			/* [annotation][out] */
			_Out_ ISystem** ppSystem) const;
	};
}