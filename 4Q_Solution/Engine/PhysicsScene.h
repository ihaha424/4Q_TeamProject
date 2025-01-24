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
			const IGeometry* geometry,
			const Engine::Transform& transform) = 0;
		virtual bool Sweep(
			AdditionalQueryData& sweepInfo,
			const IGeometry* geometry,
			const Engine::Transform& transform,
			const Engine::Math::Vector3& direction,
			float distance) = 0;
	};

	// Engine Interface
	struct Scene : IScene
	{
		virtual void Initialize(const SceneDesc& sceneDescription, const char* name = nullptr) = 0;
		virtual void Update(float deltaTime) const = 0;
		virtual void Finalize() = 0;

		virtual unsigned int GetSceneNumber() = 0;
		virtual bool AddActor(IObject* object) = 0;
	};
}
