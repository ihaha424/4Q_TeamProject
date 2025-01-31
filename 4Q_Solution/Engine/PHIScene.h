#pragma once

namespace Engine::PHI
{
	class Scene final
		: public Physics::Scene
	{
	public:
		Scene();

		void Initialize() override;
		void CollisionEvent() const override;
		void Finalize() override;

		void* GetScene() override;
		void SetSceneFilter() override;

		void SetGravity(const Math::Vector3& gravity) override;
		const Math::Vector3& GetGravity() const override;
		
		bool Raycast(
			Engine::Physics::AdditionalQueryData&	raycastInfo, 
			const Engine::Math::Vector3&			startPosition, 
			const Engine::Math::Vector3&			direction, 
			float									distance
		) override;
		bool Overlap(
			Engine::Physics::QueryData&					overlapInfo, 
			const std::string&							name,
			const Engine::Physics::GeometryDesc&		geometryDesc,
			const Engine::Physics::VerticesMeshDesc&	verticesMeshDesc,
			const Engine::Transform&					transform
		) override;
		bool Sweep(
			Engine::Physics::AdditionalQueryData&			sweepInfo, 
			const std::string&								name,
			const Engine::Physics::GeometryDesc&			geometryDesc,
			const Engine::Physics::VerticesMeshDesc&		verticesMeshDesc,
			const Engine::Transform&						transform, 
			const Engine::Math::Vector3&					direction, 
			float distance
		) override;
		
		unsigned int GetSceneIndex() override;
		
		bool AddActor(Engine::Physics::IRigidComponent* component) override;
		bool AddActor(Engine::Physics::IRigidStaticComponent* component) override;
		bool AddActor(Engine::Physics::IRigidDynamicComponent* component) override;
		bool AddActor(Engine::Physics::IRigidKinematicComponent* component) override;
		bool AddGeomtry(
			const std::string& name,
			const Engine::Physics::GeometryDesc& _geometryDesc,
			const Engine::Physics::VerticesMeshDesc& _verticesMeshDesc
		) override;

	private:
		PhysicsEngineAPI::IGeometry* FindGeometry(
			const std::string& name,
			const Engine::Physics::GeometryDesc&			geometryDesc,
			const Engine::Physics::VerticesMeshDesc&		verticesMeshDesc
		);

	private:
		PhysicsEngineAPI::IPhysicsSystem* system;
		PhysicsEngineAPI::IScene* scene;
		unsigned int sceneIndex;

		std::map<std::string, PhysicsEngineAPI::IGeometry*> geometryMap;
		PhysicsEngineAPI::Utils::DataStructure::AdditionalQueryData data;

	private:
		friend class Manager;
	};
}


