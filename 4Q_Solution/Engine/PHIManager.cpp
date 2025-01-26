#include "pch.h"
#include "PHIManager.h"


namespace Engine::PHI
{
	HRESULT BoolToHRESULT(bool isSuccess)
	{
		return isSuccess ? S_OK : S_FALSE;
	}

	Manager::Manager()
		: system{ nullptr }
	{}



	/********************************
				  Manager
	*********************************/
	void Manager::Initialize(Physics::PhysicsType physicsType)
	{
		constexpr Utility::ThrowIfFailed thrower;

		thrower(BoolToHRESULT(PhysicsEngineAPI::CreateSystem(&system, static_cast<PhysicsEngineAPI::IPhysicsSystem::PhysicsType>(physicsType))));
		thrower(BoolToHRESULT(system->CreatePhysics()));
	}

	void Manager::WorldInitialize()
	{

	}

	void Manager::Update(float deltaTime) const
	{

	}

	void Manager::Finalize()
	{
		constexpr Utility::SafeRelease releaser;

		//releaser(&scene);
		releaser(&system);
	}

	void* Manager::GetSystem()
	{
		return nullptr;
	}




	/********************************
				  Create
	*********************************/
	void Manager::CreateScene(Physics::IScene** _scene, const Physics::SceneDesc& sceneDescription, const char* name)
	{
		constexpr Utility::ThrowIfFailed thrower;

		Physics::Scene* scene = static_cast<Physics::Scene*>(*_scene);
		PhysicsEngineAPI::IScene* physicsScene = static_cast<PhysicsEngineAPI::IScene*>(scene->GetScene());

		PhysicsEngineAPI::Utils::Description::SceneDesc sceneDesc;
		sceneDesc.gravity = { sceneDescription.gravity.x, sceneDescription.gravity.y, sceneDescription.gravity.z };
		sceneDesc.CPUDispatcherCount = sceneDescription.CPUDispatcherCount;

		thrower(BoolToHRESULT(system->CreateScene(&physicsScene, sceneDesc)));
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
		system->CheckResults(sceneNumber, block);
	}

	bool Manager::CheckResults(Physics::IScene* _scene, bool block)
	{
		Physics::Scene* scene = static_cast<Physics::Scene*>(_scene);
		PhysicsEngineAPI::IScene* physicsScene = static_cast<PhysicsEngineAPI::IScene*>(scene->GetScene());

		system->CheckResults(physicsScene, block);
	}




	/********************************
				  Factory
	*********************************/
	void Manager::CreateDynamic(Physics::IRigidDynamicComponent** destObject, const Physics::RigidComponentDesc& rigidComponetDesc, const Engine::Transform& transform, float density, const Engine::Transform& shapeOffset)
	{
		system->CloneDynamic();
	}

	void Manager::CreateKinematic(Physics::IRigidKinematicComponent** destObject, const Physics::RigidComponentDesc& rigidComponetDesc, const Engine::Transform& transform, float density, const Engine::Transform& shapeOffset)
	{
		return false;
	}

	void Manager::CreateStatic(Physics::IRigidStaticComponent** destObject, const Physics::RigidComponentDesc& rigidComponetDesc, const Engine::Transform& transform, const Engine::Transform& shapeOffset)
	{
		return false;
	}

	void Manager::CloneShape(Physics::IRigidComponent** destShape, const Physics::IRigidComponent* shape, bool isExclusive)
	{
		return false;
	}

	void Manager::CloneStatic(Physics::IRigidStaticComponent** destObject, const Engine::Transform& transform, const Physics::IRigidStaticComponent* object)
	{
		return false;
	}

	void Manager::CloneDynamic(Physics::IRigidStaticComponent** destObject, const Engine::Transform& transform, const Physics::IRigidStaticComponent* object)
	{
		return false;
	}

	void Manager::CreatePlane(Physics::IRigidComponent** object, const Engine::Math::Vector4& plane, const Physics::MaterialDesc& material)
	{
		return false;
	}

	void Manager::CreatePlane(Physics::IRigidComponent** object, const Engine::Math::Vector3& point, const Engine::Math::Vector3& normal, const Physics::MaterialDesc& material)
	{
		return false;
	}

	void Manager::CreateStaticBoundBoxActor(Physics::IRigidComponent** object, const Engine::Math::Vector3& boxExtents)
	{
		return false;
	}
	
}

