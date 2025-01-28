#pragma once

namespace Engine::Component
{
	class StaticMesh final : public Mesh
	{
	public:
		void Initialize(const Modules& modules) override;
	};
}