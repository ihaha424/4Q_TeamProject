#include "pch.h"

#include "PhysXSystem.h"
#include "PhysXElement.h"
#include "PhysxCollisionEvent.h"
#include <thread>

namespace PhysicsEngineAPI
{
	using namespace Utils::DataStructure;

	PhysXSystem::PhysXSystem()
		: foundation{ NULL }
		, physics{ nullptr }
		, dispatcher{ nullptr }
		, sceneCount{ 0 }
		, sceneList{}
		, callbackCount{ 0 }
		, callbackList{}
	{
		sceneList.reserve(3);
		callbackList.reserve(3);
	}

	PhysXSystem::~PhysXSystem() { Release(); }

	void PhysXSystem::Release()
	{
		for (auto& callback : callbackList)
			SAFE_DELETE(callback);
		for (auto& scene : sceneList)
			SAFE_DELETE(scene);
		SAFE_RELEASE(dispatcher);
		SAFE_RELEASE(physics);
		DEBUG_MODE
		(
			SAFE_RELEASE(pvd);
			SAFE_RELEASE(transport);
		)
		SAFE_RELEASE(foundation);
	}







	/**************************************
	 	Create Physics System Need
	 *************************************/
	bool PhysXSystem::CreateFoundation()
	{
		foundation = PxCreateFoundation(PX_PHYSICS_VERSION, allocator, errorCallback);
		if (nullptr == foundation)
			return false;
		return true;
	}

	bool PhysXSystem::CreatePVD()
	{

		DEBUG_MODE
		(
			pvd = physx::PxCreatePvd(*foundation);
			if (nullptr == pvd)
				return false;
			transport = physx::PxDefaultPvdSocketTransportCreate("localhost", 5425, 10);
			if (nullptr == transport)
				return false;
			pvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
		)
		return true;
	}









	/**************************************
		Create Physics System
	*************************************/
	bool PhysXSystem::CreatePhysics(bool isVisualDebuger)
	{
		if (!CreateFoundation())
			return false;
		if (!CreatePVD())
			return false;

		if constexpr (DEBUG_FLAG)
		{
			DEBUG_MODE
			(
				if(isVisualDebuger)
					physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, physx::PxTolerancesScale(), true, pvd);
				else
					physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, physx::PxTolerancesScale(), true);
			foundation->setErrorLevel(physx::PxErrorCode::eMASK_ALL);
			)
		}
		else
			physics = PxCreatePhysics(PX_PHYSICS_VERSION, *foundation, physx::PxTolerancesScale(), true);
		
		if (nullptr == physics)
			return false;
		return true;
	}

	bool PhysXSystem::CreateScene(_OUT_ IScene** scene, const Utils::Description::SceneDesc& sceneDescription, const char* name)
	{	
		physx::PxSceneDesc pxSeceneDesc(physics->getTolerancesScale());
		pxSeceneDesc.gravity = physx::PxVec3(sceneDescription.gravity.x, sceneDescription.gravity.y, sceneDescription.gravity.z);
		unsigned int CPUDispatcherCount = sceneDescription.CPUDispatcherCount;
		if (CPUDispatcherCount == 0)
			CPUDispatcherCount = std::thread::hardware_concurrency();
		dispatcher = physx::PxDefaultCpuDispatcherCreate(CPUDispatcherCount);
		pxSeceneDesc.cpuDispatcher = dispatcher;
		pxSeceneDesc.filterShader = []
		(
			physx::PxFilterObjectAttributes attributes0,
			physx::PxFilterData filterData0,
			physx::PxFilterObjectAttributes attributes1,
			physx::PxFilterData filterData1,
			physx::PxPairFlags& pairFlags,
			const void* constantBlock,
			physx::PxU32 constantBlockSize
		)
		->physx::PxFilterFlags
		{
			pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT
				| physx::PxPairFlag::eTRIGGER_DEFAULT
				| physx::PxPairFlag::eNOTIFY_CONTACT_POINTS;
			return 	physx::PxFilterFlag::eDEFAULT;
		};

		PhysxCollisionEvent* callbackFunc = new PhysxCollisionEvent();
		pxSeceneDesc.simulationEventCallback = callbackFunc;
		callbackList.push_back(callbackFunc);
		callbackCount++;


		PhysXScene* newScene = new PhysXScene();
		physx::PxScene* pxScene = nullptr;
		pxScene = physics->createScene(pxSeceneDesc);
		if (nullptr == pxScene)
			return false;
		pxScene->setName(name);
		newScene->SetScene(pxScene);
		if (nullptr == newScene)
			return false;
		*scene = newScene;
		SetSceneNumber(*scene, sceneCount);
		sceneList.push_back(newScene);
		sceneCount++;
		return true;
	}

	bool PhysXSystem::CreateObject(_OUT_ IObject** object, const Utils::DataStructure::RigidBodyType& type)
	{
		physx::PxRigidActor* actor = nullptr;
		if (type == RigidBodyType::Static)
			actor = physics->createRigidStatic(physx::PxTransform({ 0.f,0.f,0.f }));
		else if (type == RigidBodyType::Dynamic)
			actor = physics->createRigidDynamic(physx::PxTransform({ 0.f,0.f,0.f }));
		else if (type == RigidBodyType::Kinematic)
			actor = nullptr; //physics->createKinematic();
		else
			return false;

		if (nullptr == actor)
			return false;

		*object = new PhysXActor(actor);
		if (nullptr == *object)
			return false;
		return true;
	}

	bool PhysXSystem::CreateGeometry(_OUT_ IGeometry** _geometry, const Utils::Description::GeometryDesc& geometryDesc, const Utils::Description::VerticesMeshDesc verticesMeshDesc)
	{
		physx::PxGeometry* geometry = nullptr;
		if (geometryDesc.type == GeometryShape::Sphere)
			geometry = new physx::PxSphereGeometry(geometryDesc.data.x);
		else if (geometryDesc.type == GeometryShape::Capsule)
			geometry = new physx::PxCapsuleGeometry(geometryDesc.data.x, geometryDesc.data.y);
		else if (geometryDesc.type == GeometryShape::Box)
			geometry = new physx::PxBoxGeometry(geometryDesc.data.x, geometryDesc.data.y, geometryDesc.data.z);
		else if (geometryDesc.type == GeometryShape::Plane)
			geometry = new physx::PxPlaneGeometry();
		else if (geometryDesc.type == GeometryShape::ConvexMesh)
		{
			if (nullptr == verticesMeshDesc.vertices.data)
				return false;
			physx::PxConvexMeshDesc description;
			description.points.count = static_cast<physx::PxU32>(verticesMeshDesc.vertices.count);
			description.points.stride = verticesMeshDesc.vertices.stride;
			description.points.data = verticesMeshDesc.vertices.data;
			description.flags = physx::PxConvexFlag::eCOMPUTE_CONVEX;

			physx::PxTolerancesScale scale;
			physx::PxCookingParams params(scale);
			physx::PxDefaultMemoryOutputStream writeBuffer;
			physx::PxConvexMeshCookingResult::Enum result;
			bool status = PxCookConvexMesh(params, description, writeBuffer, &result);

			physx::PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
			physx::PxConvexMesh* convexMesh = physics->createConvexMesh(readBuffer);;

			const physx::PxMeshScale MeshScale = physx::PxVec3{ geometryDesc.data.x, geometryDesc.data.y, geometryDesc.data.z };
			geometry = new physx::PxConvexMeshGeometry(convexMesh, MeshScale);
		}
		else if (geometryDesc.type == GeometryShape::TriangleMesh)
		{
			if (nullptr == verticesMeshDesc.vertices.data || nullptr == verticesMeshDesc.indices.data)
				return false;
			physx::PxTriangleMeshDesc description;
			description.points.count	= static_cast<physx::PxU32>(verticesMeshDesc.vertices.count);
			description.points.stride	= verticesMeshDesc.vertices.stride;
			description.points.data		= verticesMeshDesc.vertices.data;

			description.triangles.count		= static_cast<physx::PxU32>(verticesMeshDesc.indices.count);
			description.triangles.stride	= verticesMeshDesc.indices.stride;
			description.triangles.data		= verticesMeshDesc.indices.data;
			
			if (!description.isValid())
				return false;

			physx::PxTolerancesScale scale;
			physx::PxCookingParams params(scale);
			physx::PxDefaultMemoryOutputStream writeBuffer;
			physx::PxTriangleMeshCookingResult::Enum result;
			bool status = PxCookTriangleMesh(params, description, writeBuffer, &result);

			physx::PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
			physx::PxTriangleMesh* triangleMesh = physics->createTriangleMesh(readBuffer);;
			
			const physx::PxMeshScale MeshScale = physx::PxVec3{ geometryDesc.data.x, geometryDesc.data.y, geometryDesc.data.z };
			geometry = new physx::PxTriangleMeshGeometry(triangleMesh, MeshScale);
		}
		else if (geometryDesc.type == GeometryShape::Frustum)
		{
			float fovY = geometryDesc.data.x;
			float aspect = geometryDesc.data.y;
			float nearPlane = geometryDesc.data.z;
			float farPlane = geometryDesc.data.w;

			float tanHalfFovy = tanf(fovY / 2.0f);

			float nearHeight = nearPlane * tanHalfFovy;
			float nearWidth = nearHeight * aspect;
			float farHeight = farPlane * tanHalfFovy;
			float farWidth = farHeight * aspect;

			std::vector<physx::PxVec3> vertices = {
				{ -nearWidth,  nearHeight, nearPlane },  
				{  nearWidth,  nearHeight, nearPlane },  
				{  nearWidth, -nearHeight, nearPlane },  
				{ -nearWidth, -nearHeight, nearPlane },  
														 
				{ -farWidth,  farHeight, farPlane }, 
				{  farWidth,  farHeight, farPlane }, 
				{  farWidth, -farHeight, farPlane }, 
				{ -farWidth, -farHeight, farPlane }  
			};


			physx::PxConvexMeshDesc description;
			description.points.count	= static_cast<physx::PxU32>(vertices.size());
			description.points.stride	= sizeof(physx::PxVec3);
			description.points.data		= vertices.data();
			description.flags = physx::PxConvexFlag::eCOMPUTE_CONVEX;

			physx::PxTolerancesScale scale;
			physx::PxCookingParams params(scale);
			physx::PxDefaultMemoryOutputStream writeBuffer;
			physx::PxConvexMeshCookingResult::Enum result;
			bool status = PxCookConvexMesh(params, description, writeBuffer, &result);

			physx::PxDefaultMemoryInputData readBuffer(writeBuffer.getData(), writeBuffer.getSize());
			physx::PxConvexMesh* convexMesh = physics->createConvexMesh(readBuffer);;

			const physx::PxMeshScale MeshScale = physx::PxVec3{ 1.f,1.f,1.f };
			geometry = new physx::PxConvexMeshGeometry(convexMesh, MeshScale);

		}
		else
			return false;
		
		if (nullptr == geometry)
			return false;

		*_geometry = new PhysXGeometry(geometry);
		if (nullptr == *_geometry)
			return false;
		(*_geometry)->SetType(geometryDesc.type);
		return true;
	}


	bool PhysXSystem::CreateShape(_OUT_ IShape** _shape, const IGeometry* _geometry, const IMaterial* _meterial, bool isExclusive)
	{	
		physx::PxShape* shape = nullptr;
		const PhysXGeometry* geometry = dynamic_cast<const PhysXGeometry*>(_geometry);
		if (nullptr == geometry)
			return false;

		const PhysXMaterial* material = dynamic_cast<const PhysXMaterial*>(_meterial);
		if (nullptr == material)
			return false;

		shape = physics->createShape(*geometry->geometry, *material->material, isExclusive);
		if (nullptr == shape)
			return false;
		
		*_shape = new PhysXShape(shape);
		if (nullptr == *_shape)
			return false;
		return true;
	}

	bool PhysXSystem::CreateMaterial(_OUT_ IMaterial** _meterial, const Utils::Description::MaterialDesc& materialDesc)
	{
		physx::PxMaterial* material = physics->createMaterial(materialDesc.data.value[0], materialDesc.data.value[1], materialDesc.data.value[2]);
		if (nullptr == material)
			return false;

		*_meterial = new PhysXMaterial(material);
		if (nullptr == *_meterial)
			return false;
		return true;
	}







	/**************************************
		Create Camera Scene
	*************************************/

	bool PhysXSystem::CreateCameraScene(_OUT_ IScene** scene, const Utils::Description::SceneDesc& sceneDescription)
	{
		physx::PxSceneDesc pxSeceneDesc(physics->getTolerancesScale());
		pxSeceneDesc.gravity = physx::PxVec3(0.f, 0.f, 0.f);
		dispatcher = physx::PxDefaultCpuDispatcherCreate(sceneDescription.CPUDispatcherCount);
		pxSeceneDesc.cpuDispatcher = dispatcher;
		pxSeceneDesc.filterShader = []
		(
			physx::PxFilterObjectAttributes attributes0,
			physx::PxFilterData filterData0,
			physx::PxFilterObjectAttributes attributes1,
			physx::PxFilterData filterData1,
			physx::PxPairFlags& pairFlags,
			const void* constantBlock,
			physx::PxU32 constantBlockSize
			)
			->physx::PxFilterFlags
			{
				pairFlags = physx::PxPairFlag::eCONTACT_DEFAULT;

				return 	physx::PxFilterFlag::eDEFAULT;
			};

		//TODO: Count 때문에 씬을 하나 더 만들 경우 어떤식으로 관리 할지 고민해야하기는 하지만 지금 할 사항은 아님.
		//PhysxCollisionEvent* callbackFunc = new PhysxCollisionEvent();
		//pxSeceneDesc.simulationEventCallback = callbackFunc;
		//callbackList.push_back(callbackFunc);
		//callbackCount++;

		PhysXScene* newScene = new PhysXScene();
		physx::PxScene* pxScene = nullptr;
		pxScene = physics->createScene(pxSeceneDesc);
		if (nullptr == pxScene)
			return false;
		pxScene->setName("Camera Scene");
		newScene->SetScene(pxScene);
		if (nullptr == newScene)
			return false;
		*scene = newScene;
		SetSceneNumber(*scene, sceneCount);
		sceneList.push_back(newScene);
		sceneCount++;
		return true;
	}












	/**************************************
		Update Physics System (Frame Per Physics System)
	*************************************/

	void PhysXSystem::UpdateScene(unsigned int sceneNumber, const float deltaTime)
	{
		if (sceneNumber > sceneCount)
		{
			// Log Fail?
			// -> 로거를 추가해서 만들까? 아님 Exception?
		}
		(*sceneList[sceneNumber])->simulate(deltaTime);

	}

	void PhysXSystem::UpdateScene(IScene* scene, const float deltaTime)
	{
		unsigned int sceneNumber = scene->GetSceneNumber();
		if (sceneNumber > sceneCount)
		{
			// Log Fail?
			// -> 로거를 추가해서 만들까? 아님 Exception?
		}
		(*sceneList[sceneNumber])->simulate(deltaTime);
	}

	void PhysXSystem::FetchScene(unsigned int sceneNumber, bool block)
	{
		if (sceneNumber > sceneCount)
		{
			// Log Fail?
			// -> 로거를 추가해서 만들까? 아님 Exception?
		}
		(*sceneList[sceneNumber])->fetchResults(block);
	}
	void PhysXSystem::FetchScene(IScene* scene, bool block)
	{
		unsigned int sceneNumber = scene->GetSceneNumber();
		if (sceneNumber > sceneCount)
		{
			// Log Fail?
			// -> 로거를 추가해서 만들까? 아님 Exception?
		}
		(*sceneList[sceneNumber])->fetchResults(block);
	}

	bool PhysXSystem::CheckResults(unsigned int sceneNumber, bool block)
	{
		if (sceneNumber > sceneCount)
		{
			// Log Fail?
			// -> 로거를 추가해서 만들까? 아님 Exception?
		}
		return (*sceneList[sceneNumber])->checkResults(block);
	}

	bool PhysXSystem::CheckResults(IScene* scene, bool block)
	{
		unsigned int sceneNumber = scene->GetSceneNumber();
		if (sceneNumber > sceneCount)
		{
			// Log Fail?
			// -> 로거를 추가해서 만들까? 아님 Exception?
		}
		return (*sceneList[sceneNumber])->checkResults(block);
	}










	/**************************************
		Factory Physics System
	*************************************/

	bool PhysXSystem::CreateDynamic(
		_OUT_ IDynamicObject** destObject, 
		const Utils::Math::Transform& _transform, 
		const IGeometry* _geometry, 
		IMaterial* _material,
		float density, 
		const Utils::Math::Transform& _shapeOffset)
	{
		physx::PxTransform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };
		const PhysXGeometry* geometry = dynamic_cast<const PhysXGeometry*>(_geometry);
		if (nullptr == geometry)
			return false;
		PhysXMaterial* material = dynamic_cast<PhysXMaterial*>(_material);
		if (nullptr == material)
			return false;
		physx::PxTransform shapeOffset = { {_shapeOffset.position.x, _shapeOffset.position.y, _shapeOffset.position.z}, {_shapeOffset.rotation.x, _shapeOffset.rotation.y, _shapeOffset.rotation.z, _shapeOffset.rotation.w} };
		if (!shapeOffset.isValid())
			return false;

		physx::PxRigidDynamic* actor = nullptr;
		actor = PxCreateDynamic(*physics, transform, *geometry->geometry, *material->material, density, shapeOffset);
		if (nullptr == actor)
			return false;

		*destObject = new PhysXDynamicActor(actor);
		if (nullptr == *destObject)
			return false;
		return true;
	}

	bool PhysXSystem::CreateDynamic(
		_OUT_ IDynamicObject** destObject, 
		const Utils::Math::Transform& _transform, 
		IShape* _shape, 
		float density)
	{
		physx::PxTransform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };
		const PhysXShape* shape = dynamic_cast<const PhysXShape*>(_shape);
		if (nullptr == shape)
			return false;
		
		physx::PxRigidDynamic* actor = nullptr;
		actor = PxCreateDynamic(*physics, transform, *shape->shape, density);
		if (nullptr == actor)
			return false;

		*destObject = new PhysXDynamicActor(actor);
		if (nullptr == *destObject)
			return false;
		return true;
	}

	bool PhysXSystem::CreateKinematic(
		_OUT_ IKinematicObject** destObject, 
		const Utils::Math::Transform& _transform, 
		const IGeometry* _geometry, 
		IMaterial* _material, 
		float density, 
		const Utils::Math::Transform& _shapeOffset)
	{
		physx::PxTransform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };
		const PhysXGeometry* geometry = dynamic_cast<const PhysXGeometry*>(_geometry);
		if (nullptr == geometry)
			return false;
		PhysXMaterial* material = dynamic_cast<PhysXMaterial*>(_material);
		if (nullptr == material)
			return false;
		physx::PxTransform shapeOffset = { {_shapeOffset.position.x, _shapeOffset.position.y, _shapeOffset.position.z}, {_shapeOffset.rotation.x, _shapeOffset.rotation.y, _shapeOffset.rotation.z, _shapeOffset.rotation.w} };

		physx::PxRigidDynamic* actor = nullptr;
		actor = PxCreateKinematic(*physics, transform, *geometry->geometry, *material->material, density, shapeOffset);
		if (nullptr == actor)
			return false;

		*destObject = new PhysXKinematicActor(actor);
		if (nullptr == *destObject)
			return false;
		return true;
	}

	bool PhysXSystem::CreateKinematic(
		_OUT_ IKinematicObject** destObject, 
		const Utils::Math::Transform& _transform, 
		IShape* _shape, 
		float density)
	{
		physx::PxTransform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };
		const PhysXShape* shape = dynamic_cast<const PhysXShape*>(_shape);
		if (nullptr == shape)
			return false;

		physx::PxRigidDynamic* actor = nullptr;
		actor = PxCreateKinematic(*physics, transform, *shape->shape, density);
		if (nullptr == actor)
			return false;

		*destObject = new PhysXKinematicActor(actor);
		if (nullptr == *destObject)
			return false;
		return true;
	}

	bool PhysXSystem::CreateStatic(
		_OUT_ IStaticObject** destObject, 
		const Utils::Math::Transform& _transform, 
		const IGeometry* _geometry, 
		IMaterial* _material, 
		const Utils::Math::Transform& _shapeOffset)
	{
		physx::PxTransform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };
		const PhysXGeometry* geometry = dynamic_cast<const PhysXGeometry*>(_geometry);
		if (nullptr == geometry)
			return false;
		PhysXMaterial* material = dynamic_cast<PhysXMaterial*>(_material);
		if (nullptr == material)
			return false;
		physx::PxTransform shapeOffset = { {_shapeOffset.position.x, _shapeOffset.position.y, _shapeOffset.position.z}, {_shapeOffset.rotation.x, _shapeOffset.rotation.y, _shapeOffset.rotation.z, _shapeOffset.rotation.w} };

		physx::PxRigidStatic* actor = nullptr;
		actor = PxCreateStatic(*physics, transform, *geometry->geometry, *material->material, shapeOffset);
		if (nullptr == actor)
			return false;

		*destObject = new PhysXStaticActor(actor);
		if (nullptr == *destObject)
			return false;
		return true;
	}

	bool PhysXSystem::CreateStatic(
		_OUT_ IStaticObject** destObject, 
		const Utils::Math::Transform& _transform, 
		IShape* _shape)
	{
		physx::PxTransform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };
		const PhysXShape* shape = dynamic_cast<const PhysXShape*>(_shape);
		if (nullptr == shape)
			return false;

		physx::PxRigidStatic* actor = nullptr;
		actor = PxCreateStatic(*physics, transform, *shape->shape);
		if (nullptr == actor)
			return false;

		*destObject = new PhysXStaticActor(actor);
		if (nullptr == *destObject)
			return false;
		return true;
	}

	bool PhysXSystem::CloneShape(
		_OUT_ IShape** destShape, 
		const IShape* _shape, 
		bool isExclusive)
	{
		const PhysXShape* shape = dynamic_cast<const PhysXShape*>(_shape);
		if (nullptr == shape)
			return false;

		physx::PxShape* cloneShape = nullptr;
		cloneShape = PxCloneShape(*physics, *shape->shape, isExclusive);
		if (nullptr == cloneShape)
			return false;

		*destShape = new PhysXShape(cloneShape);
		if (nullptr == *destShape)
			return false;
		return true;
	}

	bool PhysXSystem::CloneStatic(
		_OUT_ IStaticObject** destObject, 
		const Utils::Math::Transform& _transform, 
		const IObject* _object)
	{
		physx::PxTransform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };

		const PhysXStaticActor* actor = dynamic_cast<const PhysXStaticActor*>(_object);
		if (nullptr == actor)
			return false;

		physx::PxRigidStatic* cloneStaticActor = PxCloneStatic(*physics, transform, *actor->actor);
		if (nullptr == cloneStaticActor)
			return false;

		*destObject = new PhysXStaticActor(cloneStaticActor);
		if (nullptr == *destObject)
			return false;
		return true;
	}

	bool PhysXSystem::CloneDynamic(
		_OUT_ IDynamicObject** destObject, 
		const Utils::Math::Transform& _transform, 
		const IObject* _object)
	{
		physx::PxTransform transform = { {_transform.position.x, _transform.position.y, _transform.position.z}, {_transform.rotation.x, _transform.rotation.y, _transform.rotation.z, _transform.rotation.w} };

		const PhysXDynamicActor* object = dynamic_cast<const PhysXDynamicActor*>(_object);
		if (nullptr == object)
			return false;

		const physx::PxRigidDynamic* actor = reinterpret_cast<const physx::PxRigidDynamic*>(object->actor);
		if (nullptr == actor)
			return false;

		physx::PxRigidDynamic* cloneStaticActor = PxCloneDynamic(*physics, transform, *actor);
		if (nullptr == cloneStaticActor)
			return false;

		*destObject = new PhysXDynamicActor(cloneStaticActor);
		if (nullptr == *destObject)
			return false;
		return true;
	}

	bool PhysXSystem::CreatePlane(
		_OUT_ IObject** object, 
		const Utils::Math::Vector4& plane, 
		IMaterial* _material)
	{
		physx::PxRigidActor* actor = nullptr;
		const PhysXMaterial* material = dynamic_cast<const PhysXMaterial*>(_material);
		if (nullptr == material)
			return false;

		physx::PxVec3 dir = { plane.x, plane.y, plane.z };
		dir.normalize();
		actor = PxCreatePlane(*physics, physx::PxPlane(dir, plane.w), *material->material);
		if (nullptr == actor)
			return false;

		*object = new PhysXActor(actor);
		if (nullptr == *object)
			return false;
		return true;
	}

	bool PhysXSystem::CreatePlane(
		_OUT_ IObject** object, 
		const Utils::Math::Vector3& point, 
		const Utils::Math::Vector3& normal, 
		IMaterial* _material)
	{
		physx::PxMaterial* mMaterial = physics->createMaterial(0.5f, 0.5f, 0.6f);
		physx::PxRigidActor* actor = nullptr;
		const PhysXMaterial* material = dynamic_cast<const PhysXMaterial*>(_material);
		if (nullptr == material)
			return false;

		actor = PxCreatePlane(*physics, physx::PxPlane({ point.x, point.y, point.z }, { normal.x, normal.y, normal.z }), *material->material);
		if (nullptr == actor)
			return false;

		*object = new PhysXActor(actor);
		if (nullptr == *object)
			return false;
		return true;
	}

	bool PhysXSystem::CreateStaticBoundBoxActor(_OUT_ IObject** object, const Utils::Math::Vector3& boxExtents)
	{
		physx::PxTransform transform = {};
		physx::PxMaterial* material = physics->createMaterial(0,0,0);
		if (nullptr == material)
			return false;
		physx::PxBoxGeometry geometry = physx::PxBoxGeometry(boxExtents.x, boxExtents.y, boxExtents.z);

		physx::PxRigidStatic* actor = nullptr;
		actor = PxCreateStatic(*physics, transform, geometry, *material);
		if (nullptr == actor)
			return false;

		*object = new PhysXStaticActor(actor);
		if (nullptr == *object)
			return false;
		return true;
	}
}
