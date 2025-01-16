#pragma once

namespace DSH::Input
{
	namespace Component
	{
		struct IComponent;
	}

	namespace Modifier
	{
		struct IModifier;
	}

	namespace Trigger
	{
		EXTERN_C const IID IID_ITrigger;

		EXTERN_C MIDL_INTERFACE("2b6d742d-d745-4af6-a994-c508c96cd9d8")
			DSH_INPUT_LIBRARY_API ITrigger : IUnknown
		{
			ITrigger() = default;
			ITrigger(const ITrigger& other) = default;
			ITrigger(ITrigger&& other) noexcept = default;
			ITrigger& operator=(const ITrigger& other) = default;
			ITrigger& operator=(ITrigger&& other) noexcept = default;
			virtual ~ITrigger() = default;

			virtual void SetComponent(
				/* [annotation][in] */
				_In_ Component::IComponent* component) = 0;

			virtual void AddModifier(
				/* [annotation][in] */
				_In_ Modifier::IModifier* modifier) = 0;
		};
	}
}
