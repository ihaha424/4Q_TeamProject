#pragma once

namespace Engine::PHI
{
	class Manager final
		: public Physics::Manager
	{
	public:
		Manager();

		/********************************
					  Manager
		*********************************/
		void Initialize(Engine::Physics::PhysicsType physicsType) override;
		void WorldInitialize() override;
		void Update(float deltaTime) override;
		void FetchSecne(bool block) override;
		void Finalize() override;
		void AttachUpdateSecne(Physics::IScene* scene) override;
		void DetachUpdateSecne(Physics::IScene* scene) override;

		void* GetSystem() const override;
		Physics::IScene* GetScene(unsigned int sceneNumber) override;

		/********************************
					  Create
		*********************************/
		void CreateScene(Physics::IScene** scene, const Physics::SceneDesc& sceneDescription, const char* name) override;
		void CreateRigidComponent(Physics::IRigidComponent** rigidComponet, const Physics::RigidComponentDesc& rigidComponetDesc) override;
		void CreateCameraScene(Physics::IScene** scene, const Physics::SceneDesc& sceneDescription) override;

		/********************************
					  Update
		*********************************/
		void UpdateSecne(unsigned int sceneNumber, const float deltaTime) override;
		void UpdateSecne(Physics::IScene* scene, const float deltaTime) override;
		void FetchSecne(unsigned int sceneNumber, bool block) override;
		void FetchSecne(Physics::IScene* scene, bool block) override;
		bool CheckResults(unsigned int sceneNumber, bool block) override;
		bool CheckResults(Physics::IScene* scene, bool block) override;

		/********************************
					  Factory
		*********************************/
		void CreateDynamic(Physics::IRigidDynamicComponent** destObject, const Physics::RigidComponentDesc& rigidComponetDesc, const Engine::Transform& transform, float density, const Engine::Transform& shapeOffset) override;
		void CreateKinematic(Physics::IRigidKinematicComponent** destObject, const Physics::RigidComponentDesc& rigidComponetDesc, const Engine::Transform& transform, float density, const Engine::Transform& shapeOffset) override;
		void CreateStatic(Physics::IRigidStaticComponent** destObject, const Physics::RigidComponentDesc& rigidComponetDesc, const Engine::Transform& transform, const Engine::Transform& shapeOffset) override;
		void CloneStatic(Physics::IRigidStaticComponent** destObject, const Engine::Transform& transform, const Physics::IRigidStaticComponent* object) override;
		void CloneDynamic(Physics::IRigidDynamicComponent** destObject, const Engine::Transform& transform, const Physics::IRigidDynamicComponent* object) override;
		void CreatePlane(Physics::IRigidComponent** object, const Engine::Math::Vector4& plane, const Physics::MaterialDesc& material) override;
		void CreatePlane(Physics::IRigidComponent** object, const Engine::Math::Vector3& point, const Engine::Math::Vector3& normal, const Physics::MaterialDesc& material) override;
		void CreateStaticBoundBoxActor(Physics::IRigidComponent** object, const Engine::Math::Vector3& boxExtents) override;

	private:
		PhysicsEngineAPI::IPhysicsSystem* system;
		std::map<unsigned int, Physics::IScene*> sceneList;

	};
}



