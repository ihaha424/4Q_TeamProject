#include "pch.h"
#include "PHIScene.h"
#include "PHIRigidComponent.h"
#include "PHIRigidStaticComponent.h"
#include "PHIRigidDynamicComponent.h"
#include "PHIRigidKinematicComponent.h"
#include "PHIManager.h"
#include "PHICoordinateConvert.h"
using namespace Engine::PHI::CONVERT;

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

	void Scene::SetSceneFilter()
	{
		scene->SetSceneFilter();
	}

	bool Scene::Raycast(Engine::Physics::AdditionalQueryData& raycastInfo, const Engine::Math::Vector3& startPosition, const Engine::Math::Vector3& direction, float distance)
	{
		bool result = scene->Raycast(data, Vector3ToPhysicsVector3(startPosition), Vector3ToPhysicsVector3(direction), distance);
		raycastInfo.flag = static_cast<Physics::QueryData::QueryFlag>(data.flag);
		raycastInfo.num = data.num;
		raycastInfo.UserDatas.reserve(data.num);
		for(size_t i = 0; i < data.num; i++)
			raycastInfo.UserDatas.push_back(static_cast<Collision<Engine::Physics::Component>*>(data.UserDatas[0])->rigidComponent);
			//raycastInfo.UserDatas.push_back(data.UserDatas[i]);
		raycastInfo.normal = PhysicsVector3ToVector3(data.normal);
		raycastInfo.position = PhysicsVector3ToVector3(data.position);
		raycastInfo.distance = data.distance;

		return result;
	}

	bool Scene::Overlap(
		Engine::Physics::QueryData&					overlapInfo, 
		const std::string&							name, 
		const Engine::Transform&					transform)
	{
		PhysicsEngineAPI::IGeometry* geometry = system->FindGeometry(name);
		if (nullptr == geometry)
			return false;

		bool result = scene->Overlap(data,
			geometry,
			TransformToPhysicsTransform(transform)
		);
		overlapInfo.flag = static_cast<Physics::QueryData::QueryFlag>(data.flag);
		overlapInfo.num = data.num;
		overlapInfo.UserDatas.reserve(data.num);
		for (size_t i = 0; i < data.num; i++)
			overlapInfo.UserDatas.push_back(static_cast<Collision<Engine::Physics::Component>*>(data.UserDatas[0])->rigidComponent);

		return result;
	}

	bool Scene::Sweep(
		Engine::Physics::AdditionalQueryData&		sweepInfo, 
		const std::string&							name, 
		const Engine::Transform&					transform, 
		const Engine::Math::Vector3&				direction, 
		float										distance)
	{
		PhysicsEngineAPI::IGeometry* geometry = system->FindGeometry(name);
		if (nullptr == geometry)
			return false;

		bool result = scene->Sweep(data,
			geometry,
			TransformToPhysicsTransform(transform),
			Vector3ToPhysicsVector3(direction),
			distance);
		sweepInfo.flag = static_cast<Physics::QueryData::QueryFlag>(data.flag);
		sweepInfo.num = data.num;
		sweepInfo.UserDatas.reserve(data.num);
		for (size_t i = 0; i < data.num; i++)
			sweepInfo.UserDatas.push_back(static_cast<Collision<Engine::Physics::Component>*>(data.UserDatas[0])->rigidComponent);
		sweepInfo.normal = PhysicsVector3ToVector3(data.normal);
		sweepInfo.position = PhysicsVector3ToVector3(data.position);
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

	void* Scene::GetScene()
	{
		return scene;
	}

	void Scene::SetGravity(const Math::Vector3& gravity)
	{
		scene->SetGravity(Vector3ToPhysicsVector3(gravity));
	}
	 Math::Vector3 Scene::GetGravity() const
	{
		return PhysicsVector3ToVector3(scene->GetGravity());
	}
}
