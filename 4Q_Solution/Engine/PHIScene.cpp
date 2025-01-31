#include "pch.h"
#include "PHIScene.h"
#include "PHIRigidComponent.h"
#include "PHIRigidStaticComponent.h"
#include "PHIRigidDynamicComponent.h"
#include "PHIRigidKinematicComponent.h"

namespace Engine::PHI
{
	Scene::Scene()
		: scene{ nullptr }
		, sceneIndex{ 0 }
	{
	}
	void Scene::Initialize()
	{
	}
	void Scene::CollisionEvent() const
	{

	}
	void Scene::Finalize()
	{
		scene->ReleaseAdditionalQueryData(data);
	}

	void Scene::SetSecneFilter()
	{
		scene->SetSecneFilter();
	}

	bool Scene::Raycast(Engine::Physics::AdditionalQueryData& raycastInfo, const Engine::Math::Vector3& startPosition, const Engine::Math::Vector3& direction, float distance)
	{
		bool result = scene->Raycast(data, { startPosition.x, startPosition.y, startPosition.z }, { direction.x, direction.y, direction.z }, distance);
		raycastInfo.flag = static_cast<Physics::QueryData::QueryFlag>(data.flag);
		raycastInfo.num = data.num;
		raycastInfo.UserDatas.reserve(data.num);
		for(size_t i = 0; i < data.num; i++)
			raycastInfo.UserDatas.push_back(data.UserDatas[i]);
		raycastInfo.normal = data.normal;
		raycastInfo.position = data.position;
		raycastInfo.distance = data.distance;

		return result;
	}

	bool Scene::Overlap(
		Engine::Physics::QueryData&					overlapInfo, 
		const std::string&							name, 
		const Engine::Physics::GeometryDesc&		geometryDesc, 
		const Engine::Physics::VerticesMeshDesc&	verticesMeshDesc, 
		const Engine::Transform&					transform)
	{
		PhysicsEngineAPI::IGeometry* geometry = FindGeometry(name, geometryDesc, verticesMeshDesc);

		bool result = scene->Overlap(data,
			geometry,
			{ { transform.position.x, transform.position.y, transform.position.z }, { transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w} });
		overlapInfo.flag = static_cast<Physics::QueryData::QueryFlag>(data.flag);
		overlapInfo.num = data.num;
		overlapInfo.UserDatas.reserve(data.num);
		for (size_t i = 0; i < data.num; i++)
			overlapInfo.UserDatas.push_back(data.UserDatas[i]);

		return result;
	}

	bool Scene::Sweep(
		Engine::Physics::AdditionalQueryData&		sweepInfo, 
		const std::string&							name, 
		const Engine::Physics::GeometryDesc&		geometryDesc, 
		const Engine::Physics::VerticesMeshDesc&	verticesMeshDesc, 
		const Engine::Transform&					transform, 
		const Engine::Math::Vector3&				direction, 
		float										distance)
	{
		PhysicsEngineAPI::IGeometry* geometry = FindGeometry(name, geometryDesc, verticesMeshDesc);

		bool result = scene->Sweep(data,
			geometry,
			{ { transform.position.x, transform.position.y, transform.position.z }, { transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w} },
			{ direction.x, direction.y, direction.z },
			distance);
		sweepInfo.flag = static_cast<Physics::QueryData::QueryFlag>(data.flag);
		sweepInfo.num = data.num;
		sweepInfo.UserDatas.reserve(data.num);
		for (size_t i = 0; i < data.num; i++)
			sweepInfo.UserDatas.push_back(data.UserDatas[i]);
		sweepInfo.normal = data.normal;
		sweepInfo.position = data.position;
		sweepInfo.distance = data.distance;

		return result;
	}


	unsigned int Scene::GetSceneIndex()
	{
		return sceneIndex;
	}

	bool Scene::AddActor(Engine::Physics::IRigidComponent* _component)
	{
		const RigidComponent* componet = static_cast<const RigidComponent*>(_component);
		return scene->AddActor(componet->object);
	}

	bool Scene::AddActor(Engine::Physics::IRigidStaticComponent* _component)
	{
		const RigidStaticComponent* componet = static_cast<const RigidStaticComponent*>(_component);
		return scene->AddActor(componet->object);
	}

	bool Scene::AddActor(Engine::Physics::IRigidDynamicComponent* _component)
	{
		const RigidDynamicComponent* componet = static_cast<const RigidDynamicComponent*>(_component);
		return scene->AddActor(componet->object);
	}

	bool Scene::AddActor(Engine::Physics::IRigidKinematicComponent* _component)
	{
		const RigidKinematicComponent* componet = static_cast<const RigidKinematicComponent*>(_component);
		return scene->AddActor(componet->object);
	}

	bool Scene::AddGeomtry(const std::string& name, const Engine::Physics::GeometryDesc& _geometryDesc, const Engine::Physics::VerticesMeshDesc& _verticesMeshDesc)
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


	void* Scene::GetScene()
	{
		return scene;
	}

	PhysicsEngineAPI::IGeometry* Scene::FindGeometry(
		const std::string& name,
		const Engine::Physics::GeometryDesc&			_geometryDesc,
		const Engine::Physics::VerticesMeshDesc&		_verticesMeshDesc
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
	void Scene::SetGravity(const Math::Vector3& gravity)
	{
		scene->SetGravity({ gravity.x, gravity.y, gravity.z});
	}
	const Math::Vector3& Scene::GetGravity() const
	{
		auto& gravity = scene->GetGravity();
		return { gravity.x, gravity.y, gravity.z };
	}
}
