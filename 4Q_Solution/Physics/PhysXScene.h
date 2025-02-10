#pragma once
#include "IScene.h"
#include "PhysXUtils.h"

namespace PhysicsEngineAPI
{
	class PhysXScene
		: public IScene
	{
	public:
		PhysXScene();
		virtual ~PhysXScene();

		// Additional to Physics System
		bool AddActor(IObject* object) override;

		// Setting Physics System
		void SetSceneFilter() override;
		void SetScene(physx::PxScene* _scene) { scene = _scene; }

		void SetGravity(const Utils::Math::Vector3& gravity) override;
		 Utils::Math::Vector3 GetGravity() const override;

		// Scene Query
		bool Raycast(
			Utils::DataStructure::AdditionalQueryData& raycastInfo,
			const Utils::Math::Vector3& startPosition, 
			const Utils::Math::Vector3& direction, 
			float distance,
			size_t maxObject
		) override;
		bool Overlap(
			Utils::DataStructure::QueryData& overlapInfo, 
			const IGeometry* geometry, 
			const Utils::Math::Transform& transform,
			size_t maxObject
		) override;		
		bool Sweep(
			Utils::DataStructure::AdditionalQueryData& sweepInfo, 
			const IGeometry* geometry,
			const Utils::Math::Transform& transform,
			const Utils::Math::Vector3& direction, 
			float distance,
			size_t maxObject
		) override;
		bool QueryFiltering() override;
		void ReleaseAdditionalQueryData(Utils::DataStructure::AdditionalQueryData& sweepInfo) override;





		physx::PxScene* operator->() { return scene; }

	public:
		void Release() override;
	private:
		physx::PxScene* scene;
		physx::PxControllerManager* controllerManager;

		physx::PxRaycastHit* hitRaycast;
		physx::PxOverlapHit* hitOverlap;
		physx::PxSweepHit* hitSweep;

		friend class PhysXSystem;
	};
}

