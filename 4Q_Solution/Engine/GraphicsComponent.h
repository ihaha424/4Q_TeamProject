#pragma once

namespace Engine::GEGraphics
{
	class Manager;
}

namespace Engine::Component
{
	class GraphicsComponent : public Component
	{
	protected:
		GraphicsComponent();

		void Initialize(const Modules& modules) override;

		GEGraphics::Manager* _graphicsManager;
	};
}