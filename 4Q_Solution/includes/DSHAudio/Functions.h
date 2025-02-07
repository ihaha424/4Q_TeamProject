#pragma once

namespace DSH::Audio
{
	struct ISystem;

	EXTERN_C struct DSH_AUDIO_LIBRARY_API CreateSystem
	{
		HRESULT STDMETHODCALLTYPE operator()(
			/* [annotation][out] */
			_Out_ ISystem** ppSystem) const;
	};
}