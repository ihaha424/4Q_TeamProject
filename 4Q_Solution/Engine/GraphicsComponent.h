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

	public:
		void Setup(Modules modules) override;

	protected:
		Engine::GEGraphics::Manager* _graphicsManager;
	};
}