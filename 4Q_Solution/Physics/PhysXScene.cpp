#include "pch.h"
#include "PhysXScene.h"
#include "PhysXActor.h"
#include "PhysXGeometry.h"

using namespace physx;
using namespace PhysicsEngineAPI::Utils::DataStructure;

namespace PhysicsEngineAPI
{
	PhysXScene::PhysXScene()
		: scene{ nullptr }
	{
		int maxObject = 4096;
		hitRaycast = new PxRaycastHit[maxObject];
		hitOverlap = new PxOverlapHit[maxObject];
		hitSweep = new physx::PxSweepHit[maxObject];
	}

	PhysXScene::~PhysXScene() { Release(); }

	void PhysXScene::Release() 
	{ 
		SAFE_RELEASE(controllerManager); 
		SAFE_RELEASE(scene); 
		SAFE_DELETE(hitRaycast);
		SAFE_DELETE(hitOverlap);
		SAFE_DELETE(hitSweep);
	}

	void PhysXScene::ReleaseAdditionalQueryData(Utils::DataStructure::AdditionalQueryData& sweepInfo)
	{
		sweepInfo.UserDatas.clear();
		sweepInfo.UserDatas.shrink_to_fit();
	}

	bool PhysXScene::AddActor(IObject* object)
	{
		physx::PxActor* actor = static_cast<physx::PxActor*>(object->GetPhysicsObject());
		if (nullptr == actor)
			return false;
		if (!scene->addActor(*actor))
			return false;
		return true;
	}

	void PhysXScene::SetSceneFilter()
	{
		//TODO:
	}

	void PhysXScene::SetGravity(const Utils::Math::Vector3& gravity)
	{
		scene->setGravity(Vector3ToPxVec3(gravity));
	}

	 Utils::Math::Vector3 PhysXScene::GetGravity() const
	{
		return PxVec3ToVector3(scene->getGravity());
	}

	bool PhysXScene::Raycast(
		Utils::DataStructure::AdditionalQueryData& raycastInfo, 
		const Utils::Math::Vector3& startPosition, 
		const Utils::Math::Vector3& direction, 
		float distance, 
		size_t maxObject)
	{
		physx::PxVec3 pos = Vector3ToPxVec3(startPosition);
		physx::PxVec3 dir = Vector3ToPxVec3(direction);
		dir.normalize();
		physx::PxReal maxDistance = distance;

		physx::PxSceneQueryFlags flag = PxHitFlag::ePOSITION | PxHitFlag::eNORMAL | PxHitFlag::eMESH_MULTIPLE;
		raycastInfo.flag = QueryData::Raycast;
		bool blockHit = false;

		int howMany = PxSceneQueryExt::raycastMultiple(*scene, pos, dir, maxDistance, flag, hitRaycast, maxObject, blockHit);
		if (howMany)
		{
			raycastInfo.num = howMany;
			for (size_t i = 0; i < howMany; i++)
			{
				physx::PxRaycastHit hitInfo = hitRaycast[i];
				raycastInfo.UserDatas.reserve(raycastInfo.num);
				if (raycastInfo.num < raycastInfo.UserDatas.size())
					raycastInfo.UserDatas[i] = static_cast<ICollision*>(hitInfo.actor->userData);
				else
					raycastInfo.UserDatas.push_back(static_cast<ICollision*>(hitInfo.actor->userData));
				raycastInfo.normal = PxVec3ToVector3(hitInfo.normal);
				raycastInfo.position = PxVec3ToVector3(hitInfo.position);
				raycastInfo.distance = hitInfo.distance;
			}
		}
		else
		{
			raycastInfo.num = 0;
		}
		return true;
	}

	bool PhysXScene::Overlap(
		Utils::DataStructure::QueryData& overlapInfo, 
		const IGeometry* _geometry, 
		const Utils::Math::Transform& _transform, 
		size_t maxObject)
	{
		physx::PxTransform transform = TransformToPxTransform(_transform);

		overlapInfo.flag = QueryData::Overlap;
		const PhysXGeometry* geometry = dynamic_cast<const PhysXGeometry*>(_geometry);
		if (nullptr == geometry)
			return false;

		int howMany = PxSceneQueryExt::overlapMultiple(*scene, *geometry->geometry, transform, hitOverlap, 4096);
		if (howMany)
		{
			overlapInfo.num = howMany;
			overlapInfo.UserDatas.reserve(overlapInfo.num);
			for (size_t i = 0; i < howMany; i++)
			{
				const PxOverlapHit& hitInfo = hitOverlap[i];
				if (i < overlapInfo.UserDatas.size())
					overlapInfo.UserDatas[i] = static_cast<ICollision*>(hitInfo.actor->userData);
				else
					overlapInfo.UserDatas.push_back(static_cast<ICollision*>(hitInfo.actor->userData));
			}
		}
		else
			overlapInfo.num = 0;
		return true;
	}

	bool PhysXScene::Sweep(
		Utils::DataStructure::AdditionalQueryData& sweepInfo, 
		const IGeometry* _geometry, 
		const Utils::Math::Transform& _transform, 
		const Utils::Math::Vector3& direction, 
		float distance,
		size_t maxObject)
	{
		physx::PxTransform transform = TransformToPxTransform(_transform);
		physx::PxVec3 dir = Vector3ToPxVec3(direction);
		dir.normalize();
		physx::PxReal maxDistance = distance;

		sweepInfo.flag = QueryData::Sweep;
		const PhysXGeometry* geometry = dynamic_cast<const PhysXGeometry*>(_geometry);
		if (nullptr == geometry)
			return false;

		physx::PxSceneQueryFlags outputFlags;
		bool blockingHit;
		outputFlags.isSet(PxSceneQueryFlag::Enum::eDEFAULT);
		int howMany = PxSceneQueryExt::sweepMultiple(*scene, *geometry->geometry, transform, dir, distance, outputFlags, hitSweep, maxObject, blockingHit);
		if (howMany)
		{
			sweepInfo.num = howMany;
			sweepInfo.UserDatas.reserve(howMany);
			for (size_t i = 0; i < sweepInfo.num; ++i)
			{
				const PxSweepHit& hitInfo = hitSweep[i];
				
				if (i < sweepInfo.UserDatas.size())
					sweepInfo.UserDatas[i] = static_cast<ICollision*>(hitInfo.actor->userData);
				else
					sweepInfo.UserDatas.push_back(static_cast<ICollision*>(hitInfo.actor->userData));
				sweepInfo.normal = PxVec3ToVector3(hitInfo.normal);
				sweepInfo.position = PxVec3ToVector3(hitInfo.position);
				sweepInfo.distance = hitInfo.distance;
			}
		}
		else
			sweepInfo.num = 0;

		return true;
	}

	bool PhysXScene::QueryFiltering()
	{
		return true;

	}
}
