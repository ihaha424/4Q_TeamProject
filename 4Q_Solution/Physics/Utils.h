#pragma once

#include "DLLExport.h"
#include "Math.h"
#include "DataStructure.h"
#include "Description.h"

namespace PhysicsEngineAPI
{
	EXTERN_C class PHYSICS_API IBase
	{
	public:
		virtual ~IBase() = default;
		virtual void Release() = 0;
	};
}
