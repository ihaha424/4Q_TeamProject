#pragma once


namespace DSH::Time
{
	struct ITickTimer;

	EXTERN_C const IID IID_ISystem;

	EXTERN_C MIDL_INTERFACE("3f4b3b1b-7b1b-4b1b-8b3b-1b7b4b3f1b7b")
		DSH_TIME_LIBRARY_API ISystem : IUnknown
	{
		ISystem() = default;
		ISystem(const ISystem& other) = default;
		ISystem(ISystem&& other) noexcept = default;
		ISystem& operator=(const ISystem& other) = default;
		ISystem& operator=(ISystem&& other) noexcept = default;
		virtual ~ISystem() = default;

		virtual HRESULT STDMETHODCALLTYPE CreateTickTimer(
			/* [annotation][out] */
			_Out_ ITickTimer** ppTickTimer) const = 0;
	};
}