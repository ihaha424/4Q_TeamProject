#pragma once

namespace DSH::Input
{
	EXTERN_C struct DSH_INPUT_LIBRARY_API CreateSystem
	{
		HRESULT STDMETHODCALLTYPE operator()(
			/* [annotation][out] */
			_Out_ ISystem** ppSystem) const;
	};
}