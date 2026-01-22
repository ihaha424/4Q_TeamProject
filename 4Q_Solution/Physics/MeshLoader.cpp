#include "pch.h"
#include "MeshLoader.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


namespace PhysicsEngineAPI
{
	bool MeshLoader::operator()(
		const char* filePath,
		std::vector<physx::PxVec3>& point,
		std::vector<physx::PxU32>& indices
	)
	{
		Assimp::Importer importer;

		const aiScene* scene = importer.ReadFile(filePath,
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_ImproveCacheLocality |
			aiProcess_PreTransformVertices);

		if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE)
			return false;

		unsigned int vertexOffset = 0;
		for (unsigned int meshIdx = 0; meshIdx < scene->mNumMeshes; meshIdx++) {
			aiMesh* mesh = scene->mMeshes[meshIdx];

			for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
				point.push_back({
					mesh->mVertices[i].x,
					mesh->mVertices[i].y,
					mesh->mVertices[i].z
					});
			}

			for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
				aiFace& face = mesh->mFaces[i];
				for (unsigned int j = 0; j < face.mNumIndices; j++) {
					indices.push_back(face.mIndices[j] + vertexOffset);
				}
			}

			vertexOffset += mesh->mNumVertices;
		}

		importer.FreeScene();
		return true;
	}
}