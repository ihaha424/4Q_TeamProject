#pragma once
#include "PhysicsManager.h"

namespace Engine::PHI
{
	class Manager final
		: public Physics::Manager
	{
	public:
		Manager();

		void Initialize(PhysicsEngineAPI::IPhysicsSystem::PhysicsType physicsType) override;
		void WorldInitialize() override;
		void Update(float deltaTime) const override;
		void Finalize() override;

	private:
		PhysicsEngineAPI::IPhysicsSystem* system;

	};
}



