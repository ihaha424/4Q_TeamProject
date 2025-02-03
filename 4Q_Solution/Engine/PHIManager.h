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
		void Initialize(Engine::Physics::PhysicsType physicsType, bool visualDebug, float length, float speed) override;
		void WorldInitialize() override;
		void Update(float deltaTime) override;
		void FetchScene(bool block) override;
		void Finalize() override;
		void AttachUpdateScene(Physics::IScene* scene) override;
		void DetachUpdateScene(Physics::IScene* scene) override;

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
		void UpdateScene(unsigned int sceneNumber, const float deltaTime) override;
		void UpdateScene(Physics::IScene* scene, const float deltaTime) override;
		void FetchScene(unsigned int sceneNumber, bool block) override;
		void FetchScene(Physics::IScene* scene, bool block) override;
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
		void CreateStaticBoundBoxActor(Physics::IRigidComponent** object, const Engine::Math::Vector3& boxExtents, const Engine::Transform& transform) override;
		void CreateControllerManager(Physics::IScene* Scene) override;
		void CreatePlayerController(Physics::IController** object, Physics::IScene* Scene, const Engine::Physics::ControllerDesc& desc) override;
	
		/********************************
					GeometryMap
		*********************************/
		bool AddGeomtry(
			const std::string& name,
			const Engine::Physics::GeometryDesc& _geometryDesc,
			const Engine::Physics::VerticesMeshDesc& _verticesMeshDesc
		) override;

		bool LoadTriangleMesh(
			const Engine::Physics::GeometryDesc& geometryDesc,
			const char* name,
			const char* filePath
		) override;

		void CreateTriangleStatic(
			Engine::Physics::IRigidStaticComponent** destObject, 
			const char* geomtryName, 
			const Engine::Physics::MaterialDesc& materialDesc, 
			const Engine::Transform& transform, 
			const Engine::Transform& shapeOffset,
			bool isExclusive
		) override;

	public:
		PhysicsEngineAPI::IGeometry* FindGeometry(
			const std::string& name,
			const Engine::Physics::GeometryDesc& geometryDesc,
			const Engine::Physics::VerticesMeshDesc& verticesMeshDesc
		);
	private:
		PhysicsEngineAPI::IPhysicsSystem* system;
		std::map<unsigned int, Physics::IScene*> sceneList;
		
		std::map<std::string, PhysicsEngineAPI::IGeometry*> geometryMap;
	};
}



