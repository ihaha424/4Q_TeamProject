#pragma once

namespace DSH::Input::Modifier
{
	EXTERN_C const IID IID_IModifier;

	EXTERN_C MIDL_INTERFACE("3f3c8b01-7d9a-4593-96da-4365ee103577")
		DSH_INPUT_LIBRARY_API IModifier : IUnknown
	{
		virtual ~IModifier() = default;
		virtual Value Modify(
			/* [annotation][in] */
			_In_ Value value) const = 0;
	};
}
