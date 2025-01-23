#pragma once
#include "IPhysicsSystem.h"
#include "PhysXUtils.h"

namespace PhysicsEngineAPI
{
	class PhysXScene;

	class PhysXSystem
		: public IPhysicsSystem
	{
		
	public:
		PhysXSystem();
		virtual ~PhysXSystem();

		// Create Physics System
		bool CreatePhysics(bool isVisualDebuger) override;
		bool CreateScene(_OUT_ IScene** scene, const Utils::Description::SceneDesc& sceneDescription, const char* name) override;
		bool CreateObject(_OUT_ IObject** object, const Utils::DataStructure::RigidBodyType& type) override;
		bool CreateGeometry(_OUT_ IGeometry** geometry, const Utils::Description::GeometryDesc& geometryDesc, const Utils::Description::VerticesMeshDesc verticesMeshDesc) override;
		bool CreateShape(_OUT_ IShape** shape, const IGeometry* geometry, const IMaterial* meterial, bool isExclusive) override;
		bool CreateMaterial(_OUT_ IMaterial** meterial, const Utils::Description::MaterialDesc& materialDesc) override;

		// Camera Scene
		bool CreateCameraScene(_OUT_ IScene** scene, const Utils::Description::SceneDesc& sceneDescription) override;
		bool CreateStaticBoundBoxActor(_OUT_ IObject** object, const Utils::Math::Vector3& boxExtents) override;

		// Frame Per Physics System
		void UpdateSecne(unsigned int sceneNumber, const float deltaTime) override;
		void UpdateSecne(IScene* scene, const float deltaTime) override;
		void FetchSecne(unsigned int sceneNumber, bool block) override;
		void FetchSecne(IScene* scene, bool block) override;
		bool CheckResults(unsigned int sceneNumber, bool block);
		bool CheckResults(IScene* scene, bool block);

		// Factory Physics System
		bool CreateDynamic(
			_OUT_ IDynamicObject** destObject,
			const Utils::Math::Transform& transform,
			const IGeometry* geometry,
			IMaterial* material,
			float density,
			const Utils::Math::Transform& shapeOffset = Utils::Math::Transform()
		) override;

		bool CreateDynamic(
			_OUT_ IDynamicObject** destObject,
			const Utils::Math::Transform& transform,
			IShape* shape,
			float density
		) override;

		bool CreateKinematic(
			_OUT_ IKinematicObject** destObject,
			const Utils::Math::Transform& transform,
			const IGeometry* geometry,
			IMaterial* material,
			float density,
			const Utils::Math::Transform& shapeOffset = Utils::Math::Transform()
		) override;

		bool CreateKinematic(
			_OUT_ IKinematicObject** destObject,
			const Utils::Math::Transform& transform,
			IShape* shape,
			float density
		) override;

		bool CreateStatic(
			_OUT_ IStaticObject** destObject,
			const Utils::Math::Transform& transform,
			const IGeometry* geometry,
			IMaterial* material,
			const Utils::Math::Transform& shapeOffset = Utils::Math::Transform()
		) override;

		bool CreateStatic(
			_OUT_ IStaticObject** destObject,
			const Utils::Math::Transform& transform,
			IShape* shape
		) override;

		bool CloneShape(
			_OUT_ IShape** destShape,
			const IShape* shape,
			bool isExclusive
		) override;

		bool CloneStatic(
			_OUT_ IStaticObject** destObject,
			const Utils::Math::Transform& transform,
			const IObject* object
		) override;

		bool CloneDynamic(
			_OUT_ IDynamicObject** destObject,
			const Utils::Math::Transform& transform,
			const IObject* object
		) override;

		bool CreatePlane(
			_OUT_ IObject** object,
			const Utils::Math::Vector4& plane,
			IMaterial* material
		) override;

		bool CreatePlane(
			_OUT_ IObject** object,
			const Utils::Math::Vector3& point,
			const Utils::Math::Vector3& normal,
			IMaterial* material
		) override;



	public:
		void Release() override;

	private:
		// Create Physics System Need
		bool CreateFoundation();
		bool CreatePVD();

	private:
		physx::PxDefaultAllocator		allocator;
		physx::PxDefaultErrorCallback	errorCallback;
		physx::PxFoundation*			foundation;

		physx::PxPhysics*				physics;
		physx::PxDefaultCpuDispatcher*	dispatcher;

		unsigned int									sceneCount;
		std::vector<PhysXScene*>						sceneList;
		unsigned int									callbackCount;
		std::vector<physx::PxSimulationEventCallback*>	callbackList;

		DEBUG_MODE
		(
			physx::PxPvd* pvd = { nullptr };
			physx::PxPvdTransport* transport = { nullptr };
		)
	};
}
