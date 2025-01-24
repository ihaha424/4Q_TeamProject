#pragma once
#include "Math.h"

namespace Engine::Physics
{
	enum class PhysicsType
	{
		Physx,
		MyPhysics,

		End
	};

	/**
	* @gravity				: Scene's Gravity
	* @CPUDispatcherCount	: CPUDispatcherCount
	*/
	struct SceneDesc
	{
		Engine::Math::Vector3 gravity;
		unsigned int CPUDispatcherCount;
	};

	/**
	 * @brief CollosionType
					Collision	:		Physical Collision flag.
					Trigger		:		Crash Identifier flag.
					Scene_Query :		Scene queries Check flag. (ray casts, overlap tests, sweeps, ...).
										Scene Query and physical simulation work separately
										Filtering is important.
											When Scene Query targets many objects, it affects performance.
	 */
	enum class CollisionType
	{
		Collision,
		Trigger,
		Scene_Query,

		End
	};

	/**
	 * @brief		: QueryData
	 * @UserDatas	: Actor's UserData
	 */
	struct QueryData
	{
		enum QueryFlag
		{
			Raycast,
			Overlap,
			Sweep,

			End
		};
		QueryFlag			flag;
		unsigned int		num;
		std::vector<void*>	UserDatas{};
	};

	struct AdditionalQueryData
		: public QueryData
	{
		Engine::Math::Vector3	normal;
		Engine::Math::Vector3	position;
		float					distance;
	};

	/*
	* @brief Basics Geometry
			Sphere			:	data.x: radius
			Capsule			:	data.x: radius,
								data.y: halfHeight
			Box				:	data.xyz: half extents¡¯ each element
			Plane			:	Parameter is ignore.
								Plane Position & Rotation is Plane's Actor's Position & Rotation.
			ConvexMesh		:	data.xyz: Scale of Mesh
			TriangleMesh	:	data.xyz: Scale of Mesh
			Frustum			:   data.x: fovY
								data.y: aspect
								data.z: nearPlane
								data.w: farPlane


	*/
	enum class GeometryShape
	{
		/**
			Basics Shape
		 */
		Sphere,
		Capsule,
		Box,
		Plane,

		/*
			Meshes or Height field
				: This geometry can Cooking Data
		*/
		ConvexMesh,
		TriangleMesh,
		//HeightField,

		/**
			Triangle or Convex derive Basics Shape
		 */
		Frustum,

		End
	};
}