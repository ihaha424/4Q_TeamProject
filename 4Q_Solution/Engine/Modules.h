#pragma once

#include "Input.h"
#include "Time.h"
#include "Graphics.h"
#include "Window.h"
#include "Physics.h"
#include "Network.h"
#include "Load.h"
#include "Content.h"
#include "Logger.h"
#include "GameState.h"

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

	namespace Physics
	{
		struct Manager;
	}

	namespace GameState
	{
		struct Manager;
	}

	struct Modules
	{
		GEGraphics::Manager* graphicsManager;
		Physics::Manager* physicsManager;
		Load::IManager* loadManager;
		GameState::IManager* gameStateManager;
	};
}