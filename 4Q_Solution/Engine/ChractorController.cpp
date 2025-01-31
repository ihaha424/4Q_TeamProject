#include "pch.h"
#include "ChractorController.h"


namespace Engine::Component
{
ChractorController::ChractorController()
	: _controller{}
{
}

void ChractorController::Initialize(const Modules& modules)
{
	Component::Initialize(modules);
	static_cast<Physics::Controller*>(_controller)->Initialize();
}

void ChractorController::FixedUpdate()
{
	Component::FixedUpdate();
	static_cast<Engine::Physics::Controller*>(_controller)->FixedUpdate();
}
}
