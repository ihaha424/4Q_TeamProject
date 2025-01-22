#include "pch.h"
#include "PhysXScene.h"
#include "PhysXActor.h"
#include "PhysXGeometry.h"

using namespace physx;
using namespace Physics::Utils::DataStructure;

namespace Physics
{
	PhysXScene::PhysXScene()
		: scene{ nullptr }
	{
	}

	PhysXScene::~PhysXScene()
	{
		if(scene)
			scene->release();
	}

	bool PhysXScene::AddActor(IObject* object)
	{
		PhysXActor* actor = dynamic_cast<PhysXActor*>(object);
		if (nullptr == actor)
			return false;
		if (!scene->addActor(*(actor->actor)))
			return false;
		return true;
	}

	void PhysXScene::SetSecneFilter()
	{
		//TODO:
	}

	bool PhysXScene::Raycast(Utils::DataStructure::AdditionalQueryData& raycastInfo, const Physics::Utils::Math::Vector3& startPosition, const Physics::Utils::Math::Vector3& direction, float distance)
	{
		PxRaycastBuffer HitBuffer;
		physx::PxVec3 pos = Vector3ToPxVec3(startPosition);
		physx::PxVec3 dir = Vector3ToPxVec3(direction);
		dir.normalize();
		physx::PxReal maxDistance = distance;

		raycastInfo.flag = QueryData::Raycast;
		bool status = scene->raycast(pos, dir, maxDistance, HitBuffer);
		if (status)
		{
			raycastInfo.num = 1;
			physx::PxRaycastHit hitInfo = HitBuffer.block;
			raycastInfo.UserDatas.push_back(hitInfo.actor->userData);
			raycastInfo.normal = PxVec3ToVector3(hitInfo.normal);
			raycastInfo.position = PxVec3ToVector3(hitInfo.position);
			raycastInfo.distance = hitInfo.distance;
		}
		else
		{
			raycastInfo.num = 0;
			return true;
		}
		return true;
	}

	bool PhysXScene::Overlap(Utils::DataStructure::QueryData& overlapInfo, const IGeometry* _geometry, const Utils::Math::Transform& _transform)
	{
		PxOverlapBuffer HitBuffer;
		physx::PxTransform transform = TransformToPxTransform(_transform);

		// temp
		PxU32 nbActors = scene->getNbActors(PxActorTypeFlag::eRIGID_STATIC | PxActorTypeFlag::eRIGID_DYNAMIC);
		PxActor** actors = new PxActor * [nbActors];
		scene->getActors(PxActorTypeFlag::eRIGID_STATIC | PxActorTypeFlag::eRIGID_DYNAMIC, actors, nbActors);
		PxSphereGeometry sphere(1000.0f);
		PxTransform queryPose(PxVec3(0.0f, 0.0f, 0.0f)); // 박스 위치
		for (PxU32 i = 0; i < nbActors; ++i) {
			PxRigidActor* actor = static_cast<PxRigidActor*>(actors[i]);
			PxTransform actorPose = actor->getGlobalPose();
			PxShape* shapes[10];
			PxU32 shapeCount = actor->getShapes(shapes, 10);
			for (PxU32 i = 0; i < shapeCount; ++i) {
				const PxGeometry& a = shapes[i]->getGeometry();
				auto b = a.getType();
				auto c = shapes[i]->getFlags();
			}
		}
		delete[] actors;
		PxQueryFilterData filterData;
		filterData.flags = PxQueryFlag::eANY_HIT; // 모든 객체 허용
		//


		overlapInfo.flag = QueryData::Overlap;
		const PhysXGeometry* geometry = dynamic_cast<const PhysXGeometry*>(_geometry);
		if (nullptr == geometry)
			return false;

		bool status = scene->overlap(/**geometry->geometry*/sphere, /*transform*/queryPose, HitBuffer, filterData);
		if (status)
		{
			overlapInfo.num = HitBuffer.nbTouches;
			overlapInfo.UserDatas.resize(overlapInfo.num);
			for (size_t i = 0; i < HitBuffer.nbTouches; i++)
			{
				const PxOverlapHit& hit = HitBuffer.getTouches()[i];
				overlapInfo.UserDatas[i] = hit.actor;
			}
		}
		else
		{
			overlapInfo.num = 0;
			return true;
		}

		return true;
	}

	bool PhysXScene::Sweep(
		Utils::DataStructure::AdditionalQueryData& sweepInfo, 
		const IGeometry* _geometry, 
		const Utils::Math::Transform& _transform, 
		const Utils::Math::Vector3& direction, 
		float distance)
	{
		PxSweepBuffer HitBuffer;
		physx::PxTransform transform = TransformToPxTransform(_transform);
		physx::PxVec3 dir = Vector3ToPxVec3(direction);
		dir.normalize();
		physx::PxReal maxDistance = distance;

		sweepInfo.flag = QueryData::Sweep;
		const PhysXGeometry* geometry = dynamic_cast<const PhysXGeometry*>(_geometry);
		if (nullptr == geometry)
			return false;

		bool status = scene->sweep(*geometry->geometry, transform, dir, maxDistance, HitBuffer);
		if (status)
		{
			sweepInfo.num = HitBuffer.getNbAnyHits();
			for (size_t i = 0; i < sweepInfo.num; ++i)
			{
				const PxSweepHit& hitInfo = HitBuffer.getAnyHit(i);
				sweepInfo.UserDatas.push_back(hitInfo.actor->userData);
				sweepInfo.normal = PxVec3ToVector3(hitInfo.normal);
				sweepInfo.position = PxVec3ToVector3(hitInfo.position);
				sweepInfo.distance = hitInfo.distance;
			}
		}
		else
		{
			sweepInfo.num = 0;
			return true;
		}
		return true;
	}

	bool PhysXScene::QueryFiltering()
	{
		return true;

	}
}
