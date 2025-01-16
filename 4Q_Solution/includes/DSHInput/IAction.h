#pragma once

namespace DSH::Input
{
	namespace Trigger
	{
		enum class Event : unsigned char;
		struct IDown;
		struct IChordAction;
	}
	EXTERN_C const IID IID_IAction;

	EXTERN_C MIDL_INTERFACE("d16d710d-209b-4d68-9927-09d684b8f582")
		DSH_INPUT_LIBRARY_API IAction : IUnknown
	{
		using Listener = std::function<void(Value)>;

		IAction() = default;
		IAction(const IAction& other) = default;
		IAction(IAction&& other) noexcept = default;
		IAction& operator=(const IAction& other) = default;
		IAction& operator=(IAction&& other) noexcept = default;
		virtual ~IAction() = default;

		virtual HRESULT STDMETHODCALLTYPE GetTrigger(
			/* [annotation][out] */
			_Out_ Trigger::IDown** ppDown) = 0;

		virtual HRESULT STDMETHODCALLTYPE GetTrigger(
			/* [annotation][out] */
			_Out_ Trigger::IChordAction** ppChordAction) = 0;

		virtual void STDMETHODCALLTYPE AddListener(
			/* [annotation][in] */
			_In_ Trigger::Event event,
			/* [annotation][in] */
			_In_ Listener listener) = 0;

		virtual bool STDMETHODCALLTYPE IsTriggered() = 0;
	};
}
