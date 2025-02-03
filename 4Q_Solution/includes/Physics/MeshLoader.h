#pragma once
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace PhysicsEngineAPI
{
	class MeshLoader
	{
	public:
		bool operator()(
			_OUT_ const Utils::Description::VerticesMeshDesc& data,
			const char* filePath,
			std::vector<physx::PxVec3>& point,
			std::vector<physx::PxU32>& indices
		);
	};
}
