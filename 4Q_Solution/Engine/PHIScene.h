#pragma once

#include "PhysicsScene.h"


namespace Engine::PHI
{
	class Scene final
		: public Physics::Scene
	{
	public:
		void Initialize(const Engine::Physics::SceneDesc& sceneDescription, const char* name) override;
		void Update(float deltaTime) const override;
		void Finalize() override;

	private:
		PhysicsEngineAPI::IScene* scene;
	};
}


