#pragma once
#include "PhysicsManager.h"

namespace Engine::PhysicsEngine
{
	class Manager final
		: public Physics::Manager
	{
	public:
		Manager();

		void Initialize() override;
		void Update(float deltaTime) const override;
		void Finalize() override;

	private:
		PhysicsEngineAPI::IPhysicsSystem* system;
	};
}



