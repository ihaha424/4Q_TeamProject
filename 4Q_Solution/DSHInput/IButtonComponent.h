#pragma once
#include "IComponent.h"

namespace DSH::Input
{
	union Value;
	namespace Component
	{
		EXTERN_C const IID IID_IButtonComponent;

		EXTERN_C MIDL_INTERFACE("da49f7fa-f32f-486f-827e-7d82a76471f9")
			DSH_INPUT_LIBRARY_API IButtonComponent : IComponent
		{
		};
	}
}
