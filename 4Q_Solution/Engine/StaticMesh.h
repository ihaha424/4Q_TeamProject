#pragma once
#include "Mesh.h"

namespace Engine::Component
{
	class StaticMesh : public Mesh
	{
	public:
		StaticMesh(std::filesystem::path filePath);
	};
}