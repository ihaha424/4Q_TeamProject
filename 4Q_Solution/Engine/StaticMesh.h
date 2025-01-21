#pragma once

namespace Engine::Component
{
	class StaticMesh final : public Mesh
	{
	public:
		StaticMesh(std::filesystem::path filePath);

	public:
		void Initialize() override;
	};
}