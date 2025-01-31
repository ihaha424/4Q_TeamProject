#pragma once

namespace Engine::Component
{
	class ChractorController : public Component
	{
	public:
		ChractorController();

		void Initialize(const Modules& modules) override;
		void FixedUpdate() override;

	private:
		Engine::Physics::IController* _controller;
	};
}
