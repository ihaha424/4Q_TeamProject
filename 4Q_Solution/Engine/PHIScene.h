#pragma once

#include "PhysicsScene.h"


namespace Engine::PHI
{
	class Scene final
		: public Physics::Scene
	{
	public:
		void Initialize() override;
		void Update(float deltaTime) const override;
		void Finalize() override;

		void SetSecneFilter() override;
		
		bool Raycast(Engine::Physics::AdditionalQueryData& raycastInfo, const Engine::Math::Vector3& startPosition, const Engine::Math::Vector3& direction, float distance) override;
		bool Overlap(Engine::Physics::QueryData& overlapInfo, const Engine::Physics::IRigidComponent* component, const Engine::Transform& transform) override;
		bool Sweep(Engine::Physics::AdditionalQueryData& sweepInfo, const Engine::Physics::IRigidComponent* component, const Engine::Transform& transform, const Engine::Math::Vector3& direction, float distance) override;
		
		unsigned int GetSceneNumber() override;
		
		bool AddActor(Engine::Physics::IRigidComponent* component) override;

	private:
		PhysicsEngineAPI::IScene* scene;
	};
}


