#include "pch.h"
#include "ChractorController.h"


namespace Engine::Component
{
	ChractorController::ChractorController()
		: _controller{nullptr}
	{
	}

	void ChractorController::Initialize(const Modules& modules)
	{
		Component::Initialize(modules);
		static_cast<Physics::Controller*>(_controller)->Initialize();
		static_cast<Physics::Controller*>(_controller)->SetOwner(GetOwner());
	}

	void ChractorController::Update(float deltaTime)
	{
		Component::Update(deltaTime);
		static_cast<Engine::Physics::Controller*>(_controller)->Update(deltaTime);
	}

	void ChractorController::FixedUpdate()
	{
		Component::FixedUpdate();
		static_cast<Engine::Physics::Controller*>(_controller)->FixedUpdate();
	}

	void ChractorController::Finalize()
	{
		Component::Finalize();
		static_cast<Engine::Physics::Controller*>(_controller)->Finalize();
	}
}
