#include "pch.h"
#include "PHIManager.h"
#include "PHIScene.h"
#include "PHIRigidComponent.h"

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
			UpdateSecne(scene.second, deltaTime);
		}
	}

	void Manager::FetchSecne(bool block)
	{
		for (auto scene : sceneList)
		{
			FetchSecne(scene.second, block);
		}
	}

	void Manager::Finalize()
	{
		constexpr Utility::SafeRelease releaser;

		releaser(&system);
	}

	void Manager::AttachUpdateSecne(Physics::IScene* scene)
	{
		auto EngineScene = static_cast<Physics::Scene*>(scene);
		sceneList[EngineScene->GetSceneIndex()] = scene;
	}

	void Manager::DetachUpdateSecne(Physics::IScene* scene)
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
		*_scene = scene;
	}

	void Manager::CreateRigidComponent(
		Physics::IRigidComponent** rigidComponet,
		const Physics::RigidComponentDesc& rigidComponetDesc
	)
	{
		constexpr Utility::ThrowIfFailed thrower;

		Physics::RigidComponent* componment = static_cast<Physics::RigidComponent*>(*rigidComponet);
		PhysicsEngineAPI::IObject* object		= static_cast<PhysicsEngineAPI::IObject*>(componment->GetPhysicsObject());
		PhysicsEngineAPI::IShape* shape			= static_cast<PhysicsEngineAPI::IShape*>(componment->GetShape());
		PhysicsEngineAPI::IGeometry* geometry	= static_cast<PhysicsEngineAPI::IGeometry*>(componment->GetGeometry());
		PhysicsEngineAPI::IMaterial* material	= static_cast<PhysicsEngineAPI::IMaterial*>(componment->GetMaterial());


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
		thrower(BoolToHRESULT(system->CreateGeometry(&geometry, geometryDesc, verticesMeshDesc)));


		PhysicsEngineAPI::Utils::Description::MaterialDesc materialDesc;
		auto& initialMeterialData = rigidComponetDesc.shapeDesc.materialDesc.data;
		materialDesc.data = { initialMeterialData.x, initialMeterialData.y, initialMeterialData.z};
		thrower(BoolToHRESULT(system->CreateMaterial(&material, materialDesc)));


		auto& isExclusive = rigidComponetDesc.shapeDesc.isExclusive;
		thrower(BoolToHRESULT(system->CreateShape(&shape, geometry, material, isExclusive)));


		PhysicsEngineAPI::Utils::DataStructure::RigidBodyType rigidBodyType;
		rigidBodyType = static_cast<PhysicsEngineAPI::Utils::DataStructure::RigidBodyType>(rigidComponetDesc.rigidType);
		thrower(BoolToHRESULT(system->CreateObject(&object, rigidBodyType)));

		object->AttachShape(shape);
	}

	void Manager::CreateCameraScene(Physics::IScene** _scene, const Physics::SceneDesc& sceneDescription)
	{
		constexpr Utility::ThrowIfFailed thrower;

		Physics::Scene* scene = static_cast<Physics::Scene*>(*_scene);
		PhysicsEngineAPI::IScene* physicsScene = static_cast<PhysicsEngineAPI::IScene*>(scene->GetScene());

		PhysicsEngineAPI::Utils::Description::SceneDesc sceneDesc;
		sceneDesc.gravity = {0,0,0 };
		sceneDesc.CPUDispatcherCount = sceneDescription.CPUDispatcherCount;

		thrower(BoolToHRESULT(system->CreateCameraScene(&physicsScene, sceneDesc)));
	}




	/********************************
				  Update
	*********************************/
	void Manager::UpdateSecne(unsigned int sceneNumber, const float deltaTime)
	{
		system->UpdateSecne(sceneNumber, deltaTime);
	}

	void Manager::UpdateSecne(Physics::IScene* _scene, const float deltaTime)
	{
		Physics::Scene* scene = static_cast<Physics::Scene*>(_scene);
		PhysicsEngineAPI::IScene* physicsScene = static_cast<PhysicsEngineAPI::IScene*>(scene->GetScene());

		system->UpdateSecne(physicsScene, deltaTime);
	}

	void Manager::FetchSecne(unsigned int sceneNumber, bool block)
	{
		system->FetchSecne(sceneNumber, block);
	}

	void Manager::FetchSecne(Physics::IScene* _scene, bool block)
	{
		Physics::Scene* scene = static_cast<Physics::Scene*>(_scene);
		PhysicsEngineAPI::IScene* physicsScene = static_cast<PhysicsEngineAPI::IScene*>(scene->GetScene());

		system->FetchSecne(physicsScene, block);
	}

	bool Manager::CheckResults(unsigned int sceneNumber, bool block)
	{
		return system->CheckResults(sceneNumber, block);
	}

	bool Manager::CheckResults(Physics::IScene* _scene, bool block)
	{
		Physics::Scene* scene = static_cast<Physics::Scene*>(_scene);
		PhysicsEngineAPI::IScene* physicsScene = static_cast<PhysicsEngineAPI::IScene*>(scene->GetScene());

		return system->CheckResults(physicsScene, block);
	}




	/********************************
				  Factory
	*********************************/
	void Manager::CreateDynamic(Physics::IRigidDynamicComponent** _destObject, const Physics::RigidComponentDesc& rigidComponetDesc, const Engine::Transform& _transform, float density, const Engine::Transform& shapeOffset)
	{
		constexpr Utility::ThrowIfFailed thrower;

		Physics::RigidDynamicComponent* destComponment = static_cast<Physics::RigidDynamicComponent*>(*_destObject);
		PhysicsEngineAPI::IDynamicObject* destObject = static_cast<PhysicsEngineAPI::IDynamicObject*>(destComponment->GetPhysicsObject());
		PhysicsEngineAPI::IShape* shape = static_cast<PhysicsEngineAPI::IShape*>(destComponment->GetShape());
		PhysicsEngineAPI::IGeometry* geometry = static_cast<PhysicsEngineAPI::IGeometry*>(destComponment->GetGeometry());
		PhysicsEngineAPI::IMaterial* material = static_cast<PhysicsEngineAPI::IMaterial*>(destComponment->GetMaterial());

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
		thrower(BoolToHRESULT(system->CreateGeometry(&geometry, geometryDesc, verticesMeshDesc)));


		PhysicsEngineAPI::Utils::Description::MaterialDesc materialDesc;
		auto& initialMeterialData = rigidComponetDesc.shapeDesc.materialDesc.data;
		materialDesc.data = { initialMeterialData.x, initialMeterialData.y, initialMeterialData.z };
		thrower(BoolToHRESULT(system->CreateMaterial(&material, materialDesc)));


		auto& isExclusive = rigidComponetDesc.shapeDesc.isExclusive;
		thrower(BoolToHRESULT(system->CreateShape(&shape, geometry, material, isExclusive)));

		thrower(BoolToHRESULT(system->CreateDynamic(&destObject, transform, shape, density)));

		destComponment->SetLocalTransform(shapeOffset);
	}

	void Manager::CreateKinematic(Physics::IRigidKinematicComponent** _destObject, const Physics::RigidComponentDesc& rigidComponetDesc, const Engine::Transform& _transform, float density, const Engine::Transform& shapeOffset)
	{
		constexpr Utility::ThrowIfFailed thrower;

		Physics::RigidKinematicComponent* destComponment = static_cast<Physics::RigidKinematicComponent*>(*_destObject);
		PhysicsEngineAPI::IKinematicObject* destObject = static_cast<PhysicsEngineAPI::IKinematicObject*>(destComponment->GetPhysicsObject());
		PhysicsEngineAPI::IShape* shape = static_cast<PhysicsEngineAPI::IShape*>(destComponment->GetShape());
		PhysicsEngineAPI::IGeometry* geometry = static_cast<PhysicsEngineAPI::IGeometry*>(destComponment->GetGeometry());
		PhysicsEngineAPI::IMaterial* material = static_cast<PhysicsEngineAPI::IMaterial*>(destComponment->GetMaterial());

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
		thrower(BoolToHRESULT(system->CreateGeometry(&geometry, geometryDesc, verticesMeshDesc)));


		PhysicsEngineAPI::Utils::Description::MaterialDesc materialDesc;
		auto& initialMeterialData = rigidComponetDesc.shapeDesc.materialDesc.data;
		materialDesc.data = { initialMeterialData.x, initialMeterialData.y, initialMeterialData.z };
		thrower(BoolToHRESULT(system->CreateMaterial(&material, materialDesc)));


		auto& isExclusive = rigidComponetDesc.shapeDesc.isExclusive;
		thrower(BoolToHRESULT(system->CreateShape(&shape, geometry, material, isExclusive)));

		thrower(BoolToHRESULT(system->CreateKinematic(&destObject, transform, shape, density)));

		destComponment->SetLocalTransform(shapeOffset);
	}

	void Manager::CreateStatic(Physics::IRigidStaticComponent** _destObject, const Physics::RigidComponentDesc& rigidComponetDesc, const Engine::Transform& _transform, const Engine::Transform& shapeOffset)
	{
		constexpr Utility::ThrowIfFailed thrower;

		Physics::RigidStaticComponent* destComponment = static_cast<Physics::RigidStaticComponent*>(*_destObject);
		PhysicsEngineAPI::IStaticObject* destObject = static_cast<PhysicsEngineAPI::IStaticObject*>(destComponment->GetPhysicsObject());
		PhysicsEngineAPI::IShape* shape = static_cast<PhysicsEngineAPI::IShape*>(destComponment->GetShape());
		PhysicsEngineAPI::IGeometry* geometry = static_cast<PhysicsEngineAPI::IGeometry*>(destComponment->GetGeometry());
		PhysicsEngineAPI::IMaterial* material = static_cast<PhysicsEngineAPI::IMaterial*>(destComponment->GetMaterial());

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
		thrower(BoolToHRESULT(system->CreateGeometry(&geometry, geometryDesc, verticesMeshDesc)));


		PhysicsEngineAPI::Utils::Description::MaterialDesc materialDesc;
		auto& initialMeterialData = rigidComponetDesc.shapeDesc.materialDesc.data;
		materialDesc.data = { initialMeterialData.x, initialMeterialData.y, initialMeterialData.z };
		thrower(BoolToHRESULT(system->CreateMaterial(&material, materialDesc)));


		auto& isExclusive = rigidComponetDesc.shapeDesc.isExclusive;
		thrower(BoolToHRESULT(system->CreateShape(&shape, geometry, material, isExclusive)));

		thrower(BoolToHRESULT(system->CreateStatic(&destObject, transform, shape)));

		destComponment->SetLocalTransform(shapeOffset);
	}

	void Manager::CloneStatic(Physics::IRigidStaticComponent** _destObject, const Engine::Transform& _transform, const Physics::IRigidStaticComponent* _object)
	{
		constexpr Utility::ThrowIfFailed thrower;

		Physics::RigidStaticComponent* destComponment = static_cast<Physics::RigidStaticComponent*>(*_destObject);
		PhysicsEngineAPI::IStaticObject* destObject = static_cast<PhysicsEngineAPI::IStaticObject*>(destComponment->GetPhysicsObject());
		
		PhysicsEngineAPI::Utils::Math::Transform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };
		
		const Physics::RigidStaticComponent* Componment = static_cast<const Physics::RigidStaticComponent*>(_object);
		PhysicsEngineAPI::IStaticObject* Object = static_cast<PhysicsEngineAPI::IStaticObject*>(Componment->GetPhysicsObject());

		thrower(BoolToHRESULT(system->CloneStatic(&destObject, transform, Object)));
	}

	void Manager::CloneDynamic(Physics::IRigidDynamicComponent** _destObject, const Engine::Transform& _transform, const Physics::IRigidDynamicComponent* _object)
	{
		constexpr Utility::ThrowIfFailed thrower;

		Physics::RigidDynamicComponent* destComponment = static_cast<Physics::RigidDynamicComponent*>(*_destObject);
		PhysicsEngineAPI::IDynamicObject* destObject = static_cast<PhysicsEngineAPI::IDynamicObject*>(destComponment->GetPhysicsObject());

		PhysicsEngineAPI::Utils::Math::Transform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };

		const Physics::RigidDynamicComponent* Componment = static_cast<const Physics::RigidDynamicComponent*>(_object);
		PhysicsEngineAPI::IDynamicObject* Object = static_cast<PhysicsEngineAPI::IDynamicObject*>(Componment->GetPhysicsObject());

		thrower(BoolToHRESULT(system->CloneDynamic(&destObject, transform, Object)));
	}

	void Manager::CreatePlane(Physics::IRigidComponent** object, const Engine::Math::Vector4& _plane, const Physics::MaterialDesc& _material)
	{
		constexpr Utility::ThrowIfFailed thrower;

		RigidComponent* destComponment = new RigidComponent();
		// PhysicsEngineAPI::IObject* destObject; //= static_cast<PhysicsEngineAPI::IObject*>(destComponment->GetPhysicsObject());
		// PhysicsEngineAPI::IMaterial* material; //= static_cast<PhysicsEngineAPI::IMaterial*>(destComponment->GetMaterial());

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

		Physics::RigidComponent* destComponment = static_cast<Physics::RigidComponent*>(*object);
		PhysicsEngineAPI::IObject* destObject = static_cast<PhysicsEngineAPI::IObject*>(destComponment->GetPhysicsObject());

		PhysicsEngineAPI::IMaterial* material = static_cast<PhysicsEngineAPI::IMaterial*>(destComponment->GetMaterial());

		PhysicsEngineAPI::Utils::Math::Vector3 point = { _point.x, _point.y, _point.z};
		PhysicsEngineAPI::Utils::Math::Vector3 normal = { _normal.x, _normal.y, _normal.z};

		PhysicsEngineAPI::Utils::Description::MaterialDesc materialDesc;
		auto& initialMeterialData = _material.data;
		materialDesc.data = { initialMeterialData.x, initialMeterialData.y, initialMeterialData.z };
		thrower(BoolToHRESULT(system->CreateMaterial(&material, materialDesc)));

		thrower(BoolToHRESULT(system->CreatePlane(&destObject, point, normal, material)));
	}

	void Manager::CreateStaticBoundBoxActor(Physics::IRigidComponent** object, const Engine::Math::Vector3& _boxExtents)
	{
		constexpr Utility::ThrowIfFailed thrower;

		Physics::RigidComponent* destComponment = static_cast<Physics::RigidComponent*>(*object);
		PhysicsEngineAPI::IObject* destObject = static_cast<PhysicsEngineAPI::IObject*>(destComponment->GetPhysicsObject());

		PhysicsEngineAPI::Utils::Math::Vector3 boxExtents = { _boxExtents.x, _boxExtents.y, _boxExtents.z };

		thrower(BoolToHRESULT(system->CreateStaticBoundBoxActor(&destObject, boxExtents)));
	}
	Physics::IScene* Manager::GetScene(unsigned int sceneNumber)
	{
		return sceneList[sceneNumber];
	}
}

