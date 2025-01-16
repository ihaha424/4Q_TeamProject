#pragma once

namespace DSH::Input::Trigger
{
	EXTERN_C const IID IID_IChordAction;

	EXTERN_C MIDL_INTERFACE("9448aea9-3784-4022-95c1-955cc71cb3d7")
		DSH_INPUT_LIBRARY_API IChordAction : ITrigger
	{
		virtual void SetPrecedingAction(
			/* [annotation][in] */
			_In_ IAction* precedingAction) = 0;
	};
}
