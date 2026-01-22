#pragma once

namespace DSH::Input
{
	struct IAction;

	EXTERN_C const IID IID_IMappingContext;

	EXTERN_C MIDL_INTERFACE("5aa7000a-b8c6-40f1-9ca6-0908c2a8ac4f")
		DSH_INPUT_LIBRARY_API IMappingContext : IUnknown
	{
		IMappingContext() = default;
		IMappingContext(const IMappingContext& other) = default;
		IMappingContext(IMappingContext&& other) noexcept = default;
		IMappingContext& operator=(const IMappingContext& other) = default;
		IMappingContext& operator=(IMappingContext&& other) noexcept = default;
		virtual ~IMappingContext() = default;

		virtual void STDMETHODCALLTYPE Update(
			/* [annotation][in] */
			_In_ float deltaTime) = 0;

		virtual void STDMETHODCALLTYPE Reset() = 0;

		virtual HRESULT STDMETHODCALLTYPE GetAction(
			/* [annotation][in] */
			_In_ const wchar_t* name,
			/* [annotation][out] */
			_Out_ IAction** ppAction) = 0;
	};
}