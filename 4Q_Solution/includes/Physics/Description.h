#pragma once

namespace PhysicsEngineAPI
{
	namespace Utils
	{
		using namespace Utils::DataStructure;
		namespace Description
		{
			EXTERN_C struct PHYSICS_API SceneDesc
			{
				/**
				 * @brief	: gravity
				 */
				Vector3			gravity;
				/**
				 * @brief	: CPUDispatcherCount
				 */
				unsigned int	CPUDispatcherCount;
			};

			EXTERN_C struct PHYSICS_API	ObjectDesc
			{

				
			};

			EXTERN_C struct PHYSICS_API	GeometryDesc
			{
				/**
				 * @brief	: Geometry's Shape
				 */
				GeometryShape	type;
				/**
				 * @brief	: Data determined by Geometry type
				 */
				Vector4	data;
			};

			EXTERN_C struct PHYSICS_API	MaterialDesc
			{
				/**
				 * @brief	:
							  value[0]: 정지 마찰 계수
							  value[1]: 동적 마찰 계수
							  value[2]: 반발 계수
				 */
				Vector3	data;
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
			EXTERN_C struct PHYSICS_API	VerticesMeshDesc
			{
				struct VerticesDesc
				{
					unsigned long long	count = -1;
					unsigned char		stride = -1;
					void*				data = nullptr;
				};
				struct IndicesDesc
				{
					unsigned long long	count = -1;
					unsigned char		stride = -1;
					void*				data = nullptr;
				};
				VerticesDesc	vertices;
				IndicesDesc		indices;
			};
		}
	}
}