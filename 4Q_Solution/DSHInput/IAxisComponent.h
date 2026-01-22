#pragma once
#include "IComponent.h"

namespace DSH::Input
{
	union Value;
	namespace Component
	{
		EXTERN_C const IID IID_IAxisComponent;

		EXTERN_C MIDL_INTERFACE("9fe457aa-060b-47c2-bdf0-7a0660760ca0")
			DSH_INPUT_LIBRARY_API IAxisComponent : IComponent
		{
		};
	}
}
