#pragma once

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
	 * @brief RigidBodyType
					Static		:
									Static objects, immobile objects in physical simulations.
									Position or rotation is set by the user.
									The physical engine won't move.
					Dynamic		:
									Objects that move according to physical simulations.
									It is influenced by the laws of physics.
									It moves in response to a collision or force.
									You can set mass, moment of inertia, coefficient of friction, coefficient of repulsion, etc.
					Kinematic	:
									It is an object that is directly controlled by the user, and is not affected by physical simulations.
									It does not move due to gravity or collisions, but provides interaction in collisions with other objects.
									It is not affected by force or gravity.
									You need to control the location directly with your code.
									Collisions can have physical effects on other objects, but they are not affected.


		Property			|				Static				|			Dynamic				|			Kinematic
		Movement:			|			  Don't move			|	Movement by Physical Engine	|  Control movement with user code
		Effects of gravity: |				  X					|				O				|			    X
		Crash handling:		|	       Crash detection			|	Crash detection & Respone	|  Crash detection & Respone(One Way)
		Performance:		|		  The most efficient		|		Rather inefficient		|	     About the middle
		Use Cases:			|		Floor, Wall, Obstacles		|	Boxes, Balls, Characters	|	Elevators, Moving platforms
	 */
	enum class RigidBodyType
	{
		Static,
		Dynamic,
		Kinematic,

		End
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
			Box				:	data.xyz: half extents’ each element
			Plane			:	Parameter is ignore.
								Plane Position & Rotation is Plane's Actor's Position & Rotation.
			ConvexMesh		:	data.xyz: Scale of Mesh
			TriangleMesh	:	data.xyz: Scale of Mesh
			Frustum			:   data.x: fovY
								data.y: aspect
								data.z: nearPlane
								data.w: farPlane
	*************************************************************************************************
		Basics Shape
				Sphere
				Capsule
				Box
				Plane

		Meshes or Height field
				: This geometry can Cooking Data
				ConvexMesh
				TriangleMesh
				HeightField

		Triangle or Convex derive Basics Shape
				Frustum


	*/
	enum class GeometryShape
	{
		Sphere,
		Capsule,
		Box,
		Plane,

		ConvexMesh,
		TriangleMesh,
		//HeightField,

		Frustum,

		End
	};

	/**
	 * @brief	: GeometryDesc
	 * type		: GeometryShape's type
	 * data		: Data - GeometryShape's Data
	 */
	struct GeometryDesc
	{
		GeometryShape	type;
		Engine::Math::Vector4	data;
	};

	/**
	 * @brief	: VerticesMeshDesc
					Basically,	The data format for vertices is Vector3 (float[3]),
								Use uint16_t for indices.
					However, if the number of indicators exceeds 65535, the data of indicators should be uint32_t.
					And, There is no limit on the number.
	 * @Example
					std::vector<Vector3> vertices;

					verticesMeshDesc.vertices.count		= vertices.size();
					verticesMeshDesc.vertices.stride	= sizeof(Vector3);
					verticesMeshDesc.vertices.data		= vertices.data();

					std::vector<uint32_t> indices;
					verticesMeshDesc.indices.count	= indices.size() / 3;
					verticesMeshDesc.indices.stride	= sizeof(uint32_t) * 3;
					verticesMeshDesc.indices.data	= indices.data();

	 */
	struct VerticesMeshDesc
	{
		struct VerticesDesc
		{
			unsigned long long	count = -1;
			unsigned char		stride = -1;
			void* data = nullptr;
		};
		struct IndicesDesc
		{
			unsigned long long	count = -1;
			unsigned char		stride = -1;
			void* data = nullptr;
		};
		VerticesDesc	vertices;
		IndicesDesc		indices;
	};

	/**
	 * @brief	:
				  value[0]: 정지 마찰 계수
				  value[1]: 동적 마찰 계수
				  value[2]: 반발 계수
	 */
	struct MaterialDesc
	{
		Engine::Math::Vector3	data;
	};

	/**
	 * @brief			: ShapeDesc
	 * geometryDesc		: GeometryDesc
	 * verticesMeshDesc	: VerticesMeshDesc
							If NotVerticesMesh, this value is not used.
	 * materialDesc		: MaterialDesc
	 * isExclusive		: Whether Shape is subordinate to the Actor
							Mostly used for Static
	 */
	struct ShapeDesc
	{
		GeometryDesc		geometryDesc;
		VerticesMeshDesc	verticesMeshDesc;
		MaterialDesc		materialDesc;
		bool				isExclusive = true;
	};

	/**
	 * @brief			: RigidComponentDesc
	 * rigidType		: RigidBodyType
	 * shapeDesc		: ShapeDesc
	 */
	struct RigidComponentDesc
	{
		RigidBodyType	rigidType;
		ShapeDesc		shapeDesc;
	};
}