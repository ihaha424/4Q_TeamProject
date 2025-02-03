#pragma once
namespace PhysicsEngineAPI
{
	__INTERFACE__
	EXTERN_C struct PHYSICS_API IMeshLoader
	{
		IMeshLoader() = default;
		IMeshLoader(const IMeshLoader& other) = default;
		IMeshLoader(IMeshLoader&& other) noexcept = default;
		IMeshLoader& operator=(const IMeshLoader& other) = default;
		IMeshLoader& operator=(IMeshLoader&& other) noexcept = default;
		virtual ~IMeshLoader() = default;

		//virtual LoadMeshData(_OUT_ const VerticesMeshDesc& data) = 0;
	};
}


