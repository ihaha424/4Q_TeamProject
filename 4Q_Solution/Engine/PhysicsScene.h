#pragma once

namespace Engine::Physics
{
	// Client Interface
	struct IScene
	{
		IScene() = default;
		IScene(const IScene& other) = default;
		IScene(IScene&& other) noexcept = default;
		IScene& operator=(const IScene& other) = default;
		IScene& operator=(IScene&& other) noexcept = default;
		virtual ~IScene() = default;

		virtual void CollisionEvent() const = 0;
		virtual void SetSecneFilter() = 0;

		/**
		 * @brief : SceneQuery
		 */
		virtual bool Raycast(
			AdditionalQueryData& raycastInfo,
			const Engine::Math::Vector3& startPosition,
			const Engine::Math::Vector3& direction,
			float distance) = 0;
		virtual bool Overlap(
			QueryData& overlapInfo,
			const std::string& name,
			const GeometryDesc&	geometryDesc,
			const VerticesMeshDesc&	verticesMeshDesc,
			const Engine::Transform& transform) = 0;
		virtual bool Sweep(
			AdditionalQueryData& sweepInfo,
			const std::string& name,
			const GeometryDesc& geometryDesc,
			const VerticesMeshDesc& verticesMeshDesc,
			const Engine::Transform& transform,
			const Engine::Math::Vector3& direction,
			float distance) = 0;

		virtual bool AddActor(IRigidComponent* component)			= 0;
		virtual bool AddActor(IRigidStaticComponent* component)		= 0;
		virtual bool AddActor(IRigidDynamicComponent* component)	= 0;
		virtual bool AddActor(IRigidKinematicComponent* component)	= 0;
	};

	// Engine Interface
	struct Scene : IScene
	{
		virtual void Initialize() = 0;
		virtual void Finalize() = 0;

		virtual void* GetScene() = 0;
		virtual unsigned int GetSceneIndex() = 0;
	};
}
