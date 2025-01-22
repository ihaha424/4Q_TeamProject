#pragma once
#include "IElementDeclaration.h"

namespace PhysicsEngineAPI
{
	__INTERFACE__
	class ISceneQuery
	{
	public:
		/**
		 * @brief : SceneQuery
		 */
		virtual bool Raycast(
			Utils::DataStructure::AdditionalQueryData& raycastInfo,
			const Utils::Math::Vector3& startPosition, 
			const Utils::Math::Vector3& direction, 
			float distance) = 0;
		virtual bool Overlap(
			Utils::DataStructure::QueryData& overlapInfo, 
			const IGeometry* geometry, 
			const Utils::Math::Transform& transform) = 0;
		virtual bool Sweep(
			Utils::DataStructure::AdditionalQueryData& sweepInfo,
			const IGeometry* geometry,
			const Utils::Math::Transform& transform,
			const Utils::Math::Vector3& direction,
			float distance) = 0;
		virtual bool QueryFiltering() = 0;
	};
}
