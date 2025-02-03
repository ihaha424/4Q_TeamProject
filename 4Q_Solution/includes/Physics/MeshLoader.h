#pragma once

namespace PhysicsEngineAPI
{
	class MeshLoader
	{
	public:
		bool operator()(
			const char* filePath,
			std::vector<physx::PxVec3>& point,
			std::vector<physx::PxU32>& indices
		);
	};
}
