#pragma once

#include <assert.h>
#include <string>
#include <filesystem>
#include <ranges>
#include <any>
#include <optional>
#include <typeinfo>
#include <typeindex>
#include <fstream>

#include "directxtk/SimpleMath.h"
#include "nlohmann/json.hpp"

#include "DSHTime/Time.h"
#include "DSHWindow/Window.h"
#include "DSHInput/Input.h"
#include "DSHLogger/Logger.h"
#include "GraphicsEngine/IGraphicsSystem.h"
#include "GraphicsEngine/ICameraSystem.h"
#include "GraphicsEngine/IRenderSystem.h"
#include "GraphicsEngine/IAnimationSystem.h"
#include "GraphicsEngine/ILightSystem.h"
#include "GraphicsEngine/ITextSystem.h"
#include "GraphicsEngine/IPostProcessSystem.h"

#include "GraphicsEngine/ICamera.h"
#include "GraphicsEngine/IAnimator.h"
#include "GraphicsEngine/IMatrix.h"
#include "GraphicsEngine/ILight.h"
#include "GraphicsEngine/IMeshRenderer.h"
#include "GraphicsEngine/ITextRenderer.h"
#include "GraphicsEngine/ISkyBoxRenderer.h"

#include "GraphicsEngine/IBloom.h"
#include "GraphicsEngine/IBlur.h"

#ifdef NDEBUG
	#define PhysicsDebuger false
#else
	#define PhysicsDebuger true
#endif

#define LEFT_HANDED_COORDINATE_SYSTEM

// If you want to left haned coirdinate system, Define This Flag.
#ifdef LEFT_HANDED_COORDINATE_SYSTEM
#define AXIS -1
#else
#define AXIS 1
#endif

#include "Physics/InterfaceAPI.h"


#include "Server/ClientEntrance.h"
#include "../Packet/ProtoInclude.h"
#include "../Packet/PacketID.h"
#include "PacketFilter.h"

#include "Math.h"

#include "Transform.h"

#include "Modules.h"

#include "Components.h"
#include "Object.h"
#include "World.h"

#include "Application.h"
