#pragma once

#include "DLLExport.h"
#include "Math.h"
#include "DataStructure.h"
#include "Description.h"

namespace PhysicsEngineAPI
{
	class IBase
	{
	public:
		virtual ~IBase();
		virtual void Release() = 0;
	};
}
