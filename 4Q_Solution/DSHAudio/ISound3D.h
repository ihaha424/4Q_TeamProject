#pragma once

namespace DSH::Audio
{
	EXTERN_C const IID IID_ISound3D;

	EXTERN_C MIDL_INTERFACE("fd420e6f-4703-47fb-aa83-64996593af4a")
		DSH_AUDIO_LIBRARY_API ISound3D : ISound
	{
		virtual HRESULT SetPosition(
			/* [annotation][in] */
			_In_ const Vector & position) = 0;

		virtual HRESULT SetVelocity(
			/* [annotation][in] */
			_In_ const Vector& velocity) = 0;
	};
}
