#pragma once

#include <assert.h>
#include <string>
#include <filesystem>
#include <ranges>
#include <any>
#include <optional>
#include <typeinfo>
#include <typeindex>

#include "directxtk/SimpleMath.h"

#include "DSHTime/Time.h"
#include "DSHWindow/Window.h"
#include "DSHInput/Input.h"
#include "GraphicsEngine/IGraphicsSystem.h"
#include "GraphicsEngine/ICameraSystem.h"
#include "GraphicsEngine/IRenderSystem.h"
#include "GraphicsEngine/IAnimationSystem.h"
#include "GraphicsEngine/ILightSystem.h"
#include "GraphicsEngine/ITextSystem.h"
#include "GraphicsEngine/ICamera.h"
#include "GraphicsEngine/IAnimator.h"
#include "GraphicsEngine/IMatrix.h"
#include "GraphicsEngine/ILight.h"
#include "GraphicsEngine/IMeshRenderer.h"
#include "GraphicsEngine/ITextRenderer.h"

#include "Math.h"

#include "Transform.h"

#include "Modules.h"

#include "Components.h"
#include "Object.h"
#include "World.h"


#include "Drive.h"
#include "Application.h"