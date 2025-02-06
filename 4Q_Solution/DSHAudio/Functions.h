#pragma once

namespace DSH::Audio
{
	struct ISystem;

	EXTERN_C struct DSH_SOUND_LIBRARY_API CreateSystem
	{
		HRESULT STDMETHODCALLTYPE operator()(
			/* [annotation][out] */
			_Out_ ISystem** ppSystem) const;
	};
}