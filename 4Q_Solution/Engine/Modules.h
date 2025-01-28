#pragma once

#include "Input.h"
#include "Time.h"
#include "Graphics.h"
#include "Window.h"
#include "Load.h"
#include "Content.h"

namespace Engine
{
	namespace Load
	{
		struct IManager;
	}

	namespace GEGraphics
	{
		class Manager;
	}
	struct Modules
	{
		GEGraphics::Manager* graphicsManager;
		Load::IManager* loadManager;
	};
}