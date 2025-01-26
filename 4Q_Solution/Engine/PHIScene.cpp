#include "pch.h"
#include "PHIScene.h"

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
	void Scene::Update(float deltaTime) const
	{
	}
	void Scene::Finalize()
	{
	}

	void Scene::SetSecneFilter()
	{
		scene->SetSecneFilter();
	}

	bool Scene::Raycast(Engine::Physics::AdditionalQueryData& raycastInfo, const Engine::Math::Vector3& startPosition, const Engine::Math::Vector3& direction, float distance)
	{
		PhysicsEngineAPI::Utils::DataStructure::AdditionalQueryData data;
		bool result = scene->Raycast(data, { startPosition.x, startPosition.y, startPosition.z }, { direction.x, direction.y, direction.z }, distance);
		raycastInfo.flag = static_cast<Physics::QueryData::QueryFlag>(data.flag);
		raycastInfo.num = data.num;
		raycastInfo.UserDatas = data.UserDatas;
		raycastInfo.normal = data.normal;
		raycastInfo.position = data.position;
		raycastInfo.distance = data.distance;
		
		return result;
	}

	bool Scene::Overlap(Engine::Physics::QueryData& overlapInfo, const Engine::Physics::IRigidComponent* _component, const Engine::Transform& transform)
	{
		const Engine::Physics::RigidComponent* componet = static_cast<const Engine::Physics::RigidComponent*>(_component);
		const PhysicsEngineAPI::IGeometry* geometry = static_cast<const PhysicsEngineAPI::IGeometry*>(componet->GetGeometry());
		PhysicsEngineAPI::Utils::DataStructure::AdditionalQueryData data;
		bool result = scene->Overlap(data,
			geometry,
			{ { transform.position.x, transform.position.y, transform.position.z }, { transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w} });
		overlapInfo.flag = static_cast<Physics::QueryData::QueryFlag>(data.flag);
		overlapInfo.num = data.num;
		overlapInfo.UserDatas = data.UserDatas;

		return result;
	}

	bool Scene::Sweep(Engine::Physics::AdditionalQueryData& sweepInfo, const Engine::Physics::IRigidComponent* _component, const Engine::Transform& transform, const Engine::Math::Vector3& direction, float distance)
	{
		const Engine::Physics::RigidComponent* componet= static_cast<const Engine::Physics::RigidComponent*>(_component);
		const PhysicsEngineAPI::IGeometry* geometry = static_cast<const PhysicsEngineAPI::IGeometry*>(componet->GetGeometry());
		PhysicsEngineAPI::Utils::DataStructure::AdditionalQueryData data;
		bool result = scene->Sweep(data,
			geometry,
			{ { transform.position.x, transform.position.y, transform.position.z }, { transform.rotation.x, transform.rotation.y, transform.rotation.z, transform.rotation.w} },
			{ direction.x, direction.y, direction.z }, 
			distance);
		sweepInfo.flag = static_cast<Physics::QueryData::QueryFlag>(data.flag);
		sweepInfo.num = data.num;
		sweepInfo.UserDatas = data.UserDatas;
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
		const Engine::Physics::RigidComponent* componet = static_cast<const Engine::Physics::RigidComponent*>(_component);
		PhysicsEngineAPI::IObject* object = static_cast<PhysicsEngineAPI::IObject*>(componet->GetPhysicsObject());
		
		return scene->AddActor(object);
	}

	void* Scene::GetScene()
	{
		return scene;
	}

}
