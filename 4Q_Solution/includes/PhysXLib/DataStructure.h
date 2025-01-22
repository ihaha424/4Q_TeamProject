#pragma once
#include <map>
#include <functional>

namespace Physics
{
	class IObject;
	namespace Utils
	{
		using namespace Physics::Utils::Math;
		namespace DataStructure
		{
			/**
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


			 */
			enum class GeometryShape
			{
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
				// Delete ToDo:
				///* 따로 구분하는게 좋을 듯
				//	Meshes or Height field
				//		: This geometry can Cooking Data
				//*/
				//HeightField,

				/**
				 * @brief Triangle or Convex derive Basics Shape
				 */
				Frustum,

				End
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
									


				//Visualization
				End
			};

			//TODO: Collition 정보 강화
			struct ContactEvent
			{
				IObject* object[2];

			};

			struct TriggerEvent
			{

			};


			//TODO: 일단 actor에 대한 데이터만 처리해놨음
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
				Vector3 normal;
				Vector3 position;
				float	distance;
			};
		}
	}
}

