#pragma once

namespace Engine::Component
{
	class StaticMesh final : public Mesh
	{
	public:
		StaticMesh(std::filesystem::path filePath, Engine::Math::Matrix* matrix);

	public:
		void Initialize() override;
	};
}