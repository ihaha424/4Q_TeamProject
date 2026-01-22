#pragma once

namespace DSH::Audio
{
	EXTERN_C const IID IID_IListener;

	EXTERN_C MIDL_INTERFACE("277ad9b6-228b-4766-a737-af0a3ccc8bb1")
		DSH_AUDIO_LIBRARY_API IListener : IUnknown
	{
		IListener() = default;
		IListener(const IListener& other) = default;
		IListener(IListener&& other) noexcept = default;
		IListener& operator=(const IListener& other) = default;
		IListener& operator=(IListener&& other) noexcept = default;
		virtual ~IListener() = default;

		virtual HRESULT Activate() = 0;

		virtual HRESULT SetPosition(
			/* [annotation][in] */
			_In_ const Vector& position) = 0;

		virtual HRESULT SetVelocity(
			/* [annotation][in] */
			_In_ const Vector& velocity) = 0;

		virtual HRESULT SetForward(
			/* [annotation][in] */
			_In_ const Vector& forward) = 0;

		virtual HRESULT SetUp(
			/* [annotation][in] */
			_In_ const Vector& up) = 0;
	};
}
