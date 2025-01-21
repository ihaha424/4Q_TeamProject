#pragma once

#include "Input.h"
#include "Time.h"
#include "Graphics.h"

namespace Engine
{
	namespace GEGraphics
	{
		class Manager;
	}
	struct Modules
	{
		GEGraphics::Manager* graphicsManager;
	};
}