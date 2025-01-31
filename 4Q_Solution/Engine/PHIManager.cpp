#include "pch.h"
#include "PHIManager.h"
#include "PHIScene.h"
#include "PHIRigidComponent.h"
#include "PHIRigidStaticComponent.h"
#include "PHIRigidDynamicComponent.h"
#include "PHIRigidKinematicComponent.h"
#include "PHIControllerComponent.h"

namespace Engine::PHI
{
	HRESULT BoolToHRESULT(bool isSuccess)
	{
		return isSuccess ? S_OK : S_FALSE;
	}

	Manager::Manager()
		: system{ nullptr }
		, sceneList{}
	{}



	/********************************
				  Manager
	*********************************/
	void Manager::Initialize(Engine::Physics::PhysicsType physicsType)
	{
		constexpr Utility::ThrowIfFailed thrower;

		int typeIndex = static_cast<int>(physicsType);
		PhysicsEngineAPI::IPhysicsSystem::PhysicsType type = static_cast<PhysicsEngineAPI::IPhysicsSystem::PhysicsType>(typeIndex);
		thrower(BoolToHRESULT(PhysicsEngineAPI::CreateSystem(&system, PhysicsEngineAPI::IPhysicsSystem::Physx)));
		thrower(BoolToHRESULT(system->CreatePhysics()));
	}

	void Manager::WorldInitialize()
	{

	}

	void Manager::Update(float deltaTime)
	{
		for (auto scene : sceneList)
		{
			UpdateScene(scene.second, deltaTime);
		}
	}

	void Manager::FetchScene(bool block)
	{
		for (auto scene : sceneList)
		{
			FetchScene(scene.second, block);
			scene.second->CollisionEvent();
		}
	}

	void Manager::Finalize()
	{
		constexpr Utility::SafeRelease releaser;

		releaser(&system);
	}

	void Manager::AttachUpdateScene(Physics::IScene* scene)
	{
		auto EngineScene = static_cast<Physics::Scene*>(scene);
		sceneList[EngineScene->GetSceneIndex()] = scene;
	}

	void Manager::DetachUpdateScene(Physics::IScene* scene)
	{
		auto EngineScene = static_cast<Physics::Scene*>(scene);
		sceneList[EngineScene->GetSceneIndex()] = nullptr;
	}

	void* Manager::GetSystem() const
	{
		return system;
	}






	/********************************
				  Create
	*********************************/
	void Manager::CreateScene(Physics::IScene** _scene, const Physics::SceneDesc& sceneDescription, const char* name)
	{
		constexpr Utility::ThrowIfFailed thrower;

		Scene* scene = new Scene();

		PhysicsEngineAPI::Utils::Description::SceneDesc sceneDesc;
		sceneDesc.gravity = { sceneDescription.gravity.x, sceneDescription.gravity.y, sceneDescription.gravity.z };
		sceneDesc.CPUDispatcherCount = sceneDescription.CPUDispatcherCount;

		thrower(BoolToHRESULT(system->CreateScene(&scene->scene, sceneDesc)));
		scene->system = this;
		*_scene = scene;
		
	}

	void Manager::CreateRigidComponent(
		Physics::IRigidComponent** rigidComponet,
		const Physics::RigidComponentDesc& rigidComponetDesc
	)
	{
		constexpr Utility::ThrowIfFailed thrower;

		RigidComponent* componment = new RigidComponent();

		PhysicsEngineAPI::Utils::Description::GeometryDesc geometryDesc;
		PhysicsEngineAPI::Utils::Description::VerticesMeshDesc verticesMeshDesc;
		geometryDesc.type					= static_cast<PhysicsEngineAPI::Utils::DataStructure::GeometryShape>(rigidComponetDesc.shapeDesc.geometryDesc.type);
		auto& initialGeometrData = rigidComponetDesc.shapeDesc.geometryDesc.data;
		geometryDesc.data					= { initialGeometrData.x, initialGeometrData.y, initialGeometrData.z, initialGeometrData.w};
		verticesMeshDesc.vertices.count		= rigidComponetDesc.shapeDesc.verticesMeshDesc.vertices.count;
		verticesMeshDesc.vertices.stride	= rigidComponetDesc.shapeDesc.verticesMeshDesc.vertices.stride;
		verticesMeshDesc.vertices.data		= rigidComponetDesc.shapeDesc.verticesMeshDesc.vertices.data;
		verticesMeshDesc.indices.count		= rigidComponetDesc.shapeDesc.verticesMeshDesc.indices.count;
		verticesMeshDesc.indices.stride		= rigidComponetDesc.shapeDesc.verticesMeshDesc.indices.stride;
		verticesMeshDesc.indices.data		= rigidComponetDesc.shapeDesc.verticesMeshDesc.indices.data;
		thrower(BoolToHRESULT(system->CreateGeometry(&componment->geometry, geometryDesc, verticesMeshDesc)));


		PhysicsEngineAPI::Utils::Description::MaterialDesc materialDesc;
		auto& initialMeterialData = rigidComponetDesc.shapeDesc.materialDesc.data;
		materialDesc.data = { initialMeterialData.x, initialMeterialData.y, initialMeterialData.z};
		thrower(BoolToHRESULT(system->CreateMaterial(&componment->material, materialDesc)));


		auto& isExclusive = rigidComponetDesc.shapeDesc.isExclusive;
		thrower(BoolToHRESULT(system->CreateShape(&componment->shape, componment->geometry, componment->material, isExclusive)));


		PhysicsEngineAPI::Utils::DataStructure::RigidBodyType rigidBodyType;
		rigidBodyType = static_cast<PhysicsEngineAPI::Utils::DataStructure::RigidBodyType>(rigidComponetDesc.rigidType);
		thrower(BoolToHRESULT(system->CreateObject(&componment->object, rigidBodyType)));

		componment->object->AttachShape(componment->shape);
		*rigidComponet = componment;
	}

	void Manager::CreateCameraScene(Physics::IScene** _scene, const Physics::SceneDesc& sceneDescription)
	{
		constexpr Utility::ThrowIfFailed thrower;

		Scene* scene = new Scene();

		PhysicsEngineAPI::Utils::Description::SceneDesc sceneDesc;
		sceneDesc.gravity = {0,0,0};
		sceneDesc.CPUDispatcherCount = sceneDescription.CPUDispatcherCount;

		thrower(BoolToHRESULT(system->CreateCameraScene(&scene->scene, sceneDesc)));
		
		scene->system = this;
		*_scene = scene;
	}




	/********************************
				  Update
	*********************************/
	void Manager::UpdateScene(unsigned int sceneNumber, const float deltaTime)
	{
		system->UpdateScene(sceneNumber, deltaTime);
	}

	void Manager::UpdateScene(Physics::IScene* _scene, const float deltaTime)
	{
		Scene* scene = static_cast<Scene*>(_scene);

		system->UpdateScene(scene->scene, deltaTime);
	}

	void Manager::FetchScene(unsigned int sceneNumber, bool block)
	{
		system->FetchScene(sceneNumber, block);
	}

	void Manager::FetchScene(Physics::IScene* _scene, bool block)
	{
		Scene* scene = static_cast<Scene*>(_scene);

		system->FetchScene(scene->scene, block);
	}

	bool Manager::CheckResults(unsigned int sceneNumber, bool block)
	{
		return system->CheckResults(sceneNumber, block);
	}

	bool Manager::CheckResults(Physics::IScene* _scene, bool block)
	{
		Scene* scene = static_cast<Scene*>(_scene);
		
		return system->CheckResults(scene->scene, block);
	}




	/********************************
				  Factory
	*********************************/
	void Manager::CreateDynamic(Physics::IRigidDynamicComponent** _destObject, const Physics::RigidComponentDesc& rigidComponetDesc, const Engine::Transform& _transform, float density, const Engine::Transform& shapeOffset)
	{
		constexpr Utility::ThrowIfFailed thrower;

		RigidDynamicComponent* destComponment = new RigidDynamicComponent();

		PhysicsEngineAPI::Utils::Math::Transform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };

		PhysicsEngineAPI::Utils::Description::GeometryDesc geometryDesc;
		PhysicsEngineAPI::Utils::Description::VerticesMeshDesc verticesMeshDesc;
		geometryDesc.type = static_cast<PhysicsEngineAPI::Utils::DataStructure::GeometryShape>(rigidComponetDesc.shapeDesc.geometryDesc.type);
		Engine::Math::Vector4 initialGeometrData = rigidComponetDesc.shapeDesc.geometryDesc.data;
		geometryDesc.data = { initialGeometrData.x, initialGeometrData.y, initialGeometrData.z, initialGeometrData.w };
		verticesMeshDesc.vertices.count = rigidComponetDesc.shapeDesc.verticesMeshDesc.vertices.count;
		verticesMeshDesc.vertices.stride = rigidComponetDesc.shapeDesc.verticesMeshDesc.vertices.stride;
		verticesMeshDesc.vertices.data = rigidComponetDesc.shapeDesc.verticesMeshDesc.vertices.data;
		verticesMeshDesc.indices.count = rigidComponetDesc.shapeDesc.verticesMeshDesc.indices.count;
		verticesMeshDesc.indices.stride = rigidComponetDesc.shapeDesc.verticesMeshDesc.indices.stride;
		verticesMeshDesc.indices.data = rigidComponetDesc.shapeDesc.verticesMeshDesc.indices.data;
		thrower(BoolToHRESULT(system->CreateGeometry(&destComponment->geometry, geometryDesc, verticesMeshDesc)));


		PhysicsEngineAPI::Utils::Description::MaterialDesc materialDesc;
		auto& initialMeterialData = rigidComponetDesc.shapeDesc.materialDesc.data;
		materialDesc.data = { initialMeterialData.x, initialMeterialData.y, initialMeterialData.z };
		thrower(BoolToHRESULT(system->CreateMaterial(&destComponment->material, materialDesc)));


		auto& isExclusive = rigidComponetDesc.shapeDesc.isExclusive;
		thrower(BoolToHRESULT(system->CreateShape(&destComponment->shape, destComponment->geometry, destComponment->material, isExclusive)));

		thrower(BoolToHRESULT(system->CreateDynamic(&destComponment->object, transform, destComponment->shape, density)));

		destComponment->SetLocalTransform(shapeOffset);
		*_destObject = destComponment;
	}

	void Manager::CreateKinematic(Physics::IRigidKinematicComponent** _destObject, const Physics::RigidComponentDesc& rigidComponetDesc, const Engine::Transform& _transform, float density, const Engine::Transform& shapeOffset)
	{
		constexpr Utility::ThrowIfFailed thrower;

		RigidKinematicComponent* destComponment = new RigidKinematicComponent();

		PhysicsEngineAPI::Utils::Math::Transform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };

		PhysicsEngineAPI::Utils::Description::GeometryDesc geometryDesc;
		PhysicsEngineAPI::Utils::Description::VerticesMeshDesc verticesMeshDesc;
		geometryDesc.type = static_cast<PhysicsEngineAPI::Utils::DataStructure::GeometryShape>(rigidComponetDesc.shapeDesc.geometryDesc.type);
		auto& initialGeometrData = rigidComponetDesc.shapeDesc.geometryDesc.data;
		geometryDesc.data = { initialGeometrData.x, initialGeometrData.y, initialGeometrData.z, initialGeometrData.w };
		verticesMeshDesc.vertices.count = rigidComponetDesc.shapeDesc.verticesMeshDesc.vertices.count;
		verticesMeshDesc.vertices.stride = rigidComponetDesc.shapeDesc.verticesMeshDesc.vertices.stride;
		verticesMeshDesc.vertices.data = rigidComponetDesc.shapeDesc.verticesMeshDesc.vertices.data;
		verticesMeshDesc.indices.count = rigidComponetDesc.shapeDesc.verticesMeshDesc.indices.count;
		verticesMeshDesc.indices.stride = rigidComponetDesc.shapeDesc.verticesMeshDesc.indices.stride;
		verticesMeshDesc.indices.data = rigidComponetDesc.shapeDesc.verticesMeshDesc.indices.data;
		thrower(BoolToHRESULT(system->CreateGeometry(&destComponment->geometry, geometryDesc, verticesMeshDesc)));


		PhysicsEngineAPI::Utils::Description::MaterialDesc materialDesc;
		auto& initialMeterialData = rigidComponetDesc.shapeDesc.materialDesc.data;
		materialDesc.data = { initialMeterialData.x, initialMeterialData.y, initialMeterialData.z };
		thrower(BoolToHRESULT(system->CreateMaterial(&destComponment->material, materialDesc)));


		auto& isExclusive = rigidComponetDesc.shapeDesc.isExclusive;
		thrower(BoolToHRESULT(system->CreateShape(&destComponment->shape, destComponment->geometry, destComponment->material, isExclusive)));

		thrower(BoolToHRESULT(system->CreateKinematic(&destComponment->object, transform, destComponment->shape, density)));

		destComponment->SetLocalTransform(shapeOffset);
		*_destObject = destComponment;
	}

	void Manager::CreateStatic(Physics::IRigidStaticComponent** _destObject, const Physics::RigidComponentDesc& rigidComponetDesc, const Engine::Transform& _transform, const Engine::Transform& shapeOffset)
	{
		constexpr Utility::ThrowIfFailed thrower;

		RigidStaticComponent* destComponment = new RigidStaticComponent();

		PhysicsEngineAPI::Utils::Math::Transform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };

		PhysicsEngineAPI::Utils::Description::GeometryDesc geometryDesc;
		PhysicsEngineAPI::Utils::Description::VerticesMeshDesc verticesMeshDesc;
		geometryDesc.type = static_cast<PhysicsEngineAPI::Utils::DataStructure::GeometryShape>(rigidComponetDesc.shapeDesc.geometryDesc.type);
		auto& initialGeometrData = rigidComponetDesc.shapeDesc.geometryDesc.data;
		geometryDesc.data = { initialGeometrData.x, initialGeometrData.y, initialGeometrData.z, initialGeometrData.w };
		verticesMeshDesc.vertices.count = rigidComponetDesc.shapeDesc.verticesMeshDesc.vertices.count;
		verticesMeshDesc.vertices.stride = rigidComponetDesc.shapeDesc.verticesMeshDesc.vertices.stride;
		verticesMeshDesc.vertices.data = rigidComponetDesc.shapeDesc.verticesMeshDesc.vertices.data;
		verticesMeshDesc.indices.count = rigidComponetDesc.shapeDesc.verticesMeshDesc.indices.count;
		verticesMeshDesc.indices.stride = rigidComponetDesc.shapeDesc.verticesMeshDesc.indices.stride;
		verticesMeshDesc.indices.data = rigidComponetDesc.shapeDesc.verticesMeshDesc.indices.data;
		thrower(BoolToHRESULT(system->CreateGeometry(&destComponment->geometry, geometryDesc, verticesMeshDesc)));


		PhysicsEngineAPI::Utils::Description::MaterialDesc materialDesc;
		auto& initialMeterialData = rigidComponetDesc.shapeDesc.materialDesc.data;
		materialDesc.data = { initialMeterialData.x, initialMeterialData.y, initialMeterialData.z };
		thrower(BoolToHRESULT(system->CreateMaterial(&destComponment->material, materialDesc)));


		auto& isExclusive = rigidComponetDesc.shapeDesc.isExclusive;
		thrower(BoolToHRESULT(system->CreateShape(&destComponment->shape, destComponment->geometry, destComponment->material, isExclusive)));

		thrower(BoolToHRESULT(system->CreateStatic(&destComponment->object, transform, destComponment->shape)));

		destComponment->SetLocalTransform(shapeOffset);
		*_destObject = destComponment;
	}

	void Manager::CloneStatic(Physics::IRigidStaticComponent** _destObject, const Engine::Transform& _transform, const Physics::IRigidStaticComponent* _object)
	{
		constexpr Utility::ThrowIfFailed thrower;

		RigidStaticComponent* destComponment = new RigidStaticComponent();
		
		PhysicsEngineAPI::Utils::Math::Transform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };
		
		const RigidStaticComponent* Componment = static_cast<const RigidStaticComponent*>(_object);

		thrower(BoolToHRESULT(system->CloneStatic(&destComponment->object, transform, Componment->object)));
	}

	void Manager::CloneDynamic(Physics::IRigidDynamicComponent** _destObject, const Engine::Transform& _transform, const Physics::IRigidDynamicComponent* _object)
	{
		constexpr Utility::ThrowIfFailed thrower;

		RigidDynamicComponent* destComponment = new RigidDynamicComponent();

		PhysicsEngineAPI::Utils::Math::Transform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };

		const RigidDynamicComponent* Componment = static_cast<const RigidDynamicComponent*>(_object);

		thrower(BoolToHRESULT(system->CloneDynamic(&destComponment->object, transform, Componment->object)));
		*_destObject = destComponment;
	}

	void Manager::CreatePlane(Physics::IRigidComponent** object, const Engine::Math::Vector4& _plane, const Physics::MaterialDesc& _material)
	{
		constexpr Utility::ThrowIfFailed thrower;

		RigidComponent* destComponment = new RigidComponent();
		
		PhysicsEngineAPI::Utils::Math::Vector4 plane = { _plane.x, _plane.y, _plane.z, _plane.w};

		PhysicsEngineAPI::Utils::Description::MaterialDesc materialDesc;
		auto& initialMeterialData = _material.data;
		materialDesc.data = { initialMeterialData.x, initialMeterialData.y, initialMeterialData.z };
		thrower(BoolToHRESULT(system->CreateMaterial(&destComponment->material, materialDesc)));

		thrower(BoolToHRESULT(system->CreatePlane(&destComponment->object, plane, destComponment->material)));
		*object = destComponment;
	}

	void Manager::CreatePlane(Physics::IRigidComponent** object, const Engine::Math::Vector3& _point, const Engine::Math::Vector3& _normal, const Physics::MaterialDesc& _material)
	{
		constexpr Utility::ThrowIfFailed thrower;

		RigidComponent* destComponment = new RigidComponent();
			
		PhysicsEngineAPI::IMaterial* material = static_cast<PhysicsEngineAPI::IMaterial*>(destComponment->material);

		PhysicsEngineAPI::Utils::Math::Vector3 point = { _point.x, _point.y, _point.z};
		PhysicsEngineAPI::Utils::Math::Vector3 normal = { _normal.x, _normal.y, _normal.z};

		PhysicsEngineAPI::Utils::Description::MaterialDesc materialDesc;
		auto& initialMeterialData = _material.data;
		materialDesc.data = { initialMeterialData.x, initialMeterialData.y, initialMeterialData.z };
		thrower(BoolToHRESULT(system->CreateMaterial(&material, materialDesc)));

		thrower(BoolToHRESULT(system->CreatePlane(&destComponment->object, point, normal, material)));
		*object = destComponment;
	}

	void Manager::CreateStaticBoundBoxActor(Physics::IRigidComponent** object, const Engine::Math::Vector3& _boxExtents)
	{
		constexpr Utility::ThrowIfFailed thrower;

		RigidComponent* destComponment = new RigidComponent();

		PhysicsEngineAPI::Utils::Math::Vector3 boxExtents = { _boxExtents.x, _boxExtents.y, _boxExtents.z };

		thrower(BoolToHRESULT(system->CreateStaticBoundBoxActor(&destComponment->object, boxExtents)));
		*object = destComponment;
	}

	void Manager::CreateControllerManager(Physics::IScene* _scene)
	{
		constexpr Utility::ThrowIfFailed thrower;

		Scene* scene = static_cast<Scene*>(_scene);
		thrower(BoolToHRESULT(system->CreateControllerManager(scene->scene)));
	}

	void Manager::CreatePlayerController(Physics::IController** object, Physics::IScene* _scene, const Physics::ControllerDesc& _desc)
	{
		constexpr Utility::ThrowIfFailed thrower;

		Scene* scene = static_cast<Scene*>(_scene);
		PhysicsEngineAPI::Utils::Description::ControllerDesc desc;
		desc.gravity = { _desc.gravity.x,_desc.gravity.y, _desc.gravity.z };
		desc.position = { _desc.position.x, _desc.position.y, _desc.position.z };
		desc.upDirection = { _desc.upDirection.x,_desc.upDirection.y, _desc.upDirection.z };
		desc.slopeLimit	= _desc.slopeLimit;
		desc.invisibleWallHeight = _desc.invisibleWallHeight;
		desc.maxJumpHeight = _desc.maxJumpHeight;
		desc.contactOffset = _desc.contactOffset;
		desc.stepOffset = _desc.stepOffset;
		desc.slopeMode = static_cast<PhysicsEngineAPI::Utils::DataStructure::ControllerSlope>(_desc.slopeMode);
		desc.material = { _desc.material.x,_desc.material.y, _desc.material.z };
		desc.radius	 = _desc.radius;
		desc.height	 = _desc.height;
		desc.climbinMode = static_cast<PhysicsEngineAPI::Utils::DataStructure::CapsuleClimbingMode>(_desc.climbinMode);

		Controller* controller = new Controller();
		thrower(BoolToHRESULT(system->CreatePlayerController(&controller->controller, scene->scene, desc)));
	
		*object = controller;
	}

	Physics::IScene* Manager::GetScene(unsigned int sceneNumber)
	{
		return sceneList[sceneNumber];
	}


	/********************************
				GeometryMap
	*********************************/
	bool Manager::AddGeomtry(const std::string& name, const Engine::Physics::GeometryDesc& _geometryDesc, const Engine::Physics::VerticesMeshDesc& _verticesMeshDesc)
	{
		PhysicsEngineAPI::IGeometry* geometry = nullptr;
		bool result = false;
		auto iter = geometryMap.find(name);
		if (iter == geometryMap.end())
		{
			PhysicsEngineAPI::Utils::Description::GeometryDesc geometryDesc;
			PhysicsEngineAPI::Utils::Description::VerticesMeshDesc verticesMeshDesc;
			geometryDesc.type = static_cast<PhysicsEngineAPI::Utils::DataStructure::GeometryShape>(_geometryDesc.type);
			auto& initialGeometrData = _geometryDesc.data;
			geometryDesc.data = { initialGeometrData.x, initialGeometrData.y, initialGeometrData.z, initialGeometrData.w };
			verticesMeshDesc.vertices.count = _verticesMeshDesc.vertices.count;
			verticesMeshDesc.vertices.stride = _verticesMeshDesc.vertices.stride;
			verticesMeshDesc.vertices.data = _verticesMeshDesc.vertices.data;
			verticesMeshDesc.indices.count = _verticesMeshDesc.indices.count;
			verticesMeshDesc.indices.stride = _verticesMeshDesc.indices.stride;
			verticesMeshDesc.indices.data = _verticesMeshDesc.indices.data;
			result = system->CreateGeometry(&geometry, geometryDesc, verticesMeshDesc);
			geometryMap[name] = geometry;
		}

		return result;
	}

	bool Manager::LoadTriangleMesh(
		const Engine::Physics::GeometryDesc& _geometryDesc,
		const char* name,
		const char* filePath
	)
	{
		PhysicsEngineAPI::IGeometry* geometry = nullptr;
		bool result = false;
		auto iter = geometryMap.find(name);
		if (iter == geometryMap.end())
		{
			PhysicsEngineAPI::Utils::Description::GeometryDesc geometryDesc;
			geometryDesc.type = static_cast<PhysicsEngineAPI::Utils::DataStructure::GeometryShape>(_geometryDesc.type);
			auto& initialGeometrData = _geometryDesc.data;
			geometryDesc.data = { initialGeometrData.x, initialGeometrData.y, initialGeometrData.z, initialGeometrData.w };

			result = system->LoadTriangleMesh(&geometry, geometryDesc, filePath);
			geometryMap[name] = geometry;
		}

		return result;
	}

	PhysicsEngineAPI::IGeometry* Manager::FindGeometry(
		const std::string& name,
		const Engine::Physics::GeometryDesc& _geometryDesc,
		const Engine::Physics::VerticesMeshDesc& _verticesMeshDesc
	)
	{
		PhysicsEngineAPI::IGeometry* geometry = nullptr;
		auto iter = geometryMap.find(name);
		if (iter == geometryMap.end())
		{
			PhysicsEngineAPI::Utils::Description::GeometryDesc geometryDesc;
			PhysicsEngineAPI::Utils::Description::VerticesMeshDesc verticesMeshDesc;
			geometryDesc.type = static_cast<PhysicsEngineAPI::Utils::DataStructure::GeometryShape>(_geometryDesc.type);
			auto& initialGeometrData = _geometryDesc.data;
			geometryDesc.data = { initialGeometrData.x, initialGeometrData.y, initialGeometrData.z, initialGeometrData.w };
			verticesMeshDesc.vertices.count = _verticesMeshDesc.vertices.count;
			verticesMeshDesc.vertices.stride = _verticesMeshDesc.vertices.stride;
			verticesMeshDesc.vertices.data = _verticesMeshDesc.vertices.data;
			verticesMeshDesc.indices.count = _verticesMeshDesc.indices.count;
			verticesMeshDesc.indices.stride = _verticesMeshDesc.indices.stride;
			verticesMeshDesc.indices.data = _verticesMeshDesc.indices.data;
			system->CreateGeometry(&geometry, geometryDesc, verticesMeshDesc);
			geometryMap[name] = geometry;
		}
		else
			geometry = iter->second;

		return geometry;
	}
}

