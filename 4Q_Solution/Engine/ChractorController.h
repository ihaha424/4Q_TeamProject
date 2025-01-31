#pragma once

namespace Engine::Component
{
	class ChractorController : public Component
	{
	public:
		ChractorController();

		void Initialize(const Modules& modules) override;
		void FixedUpdate() override;
		void Finalize() override;

	public:
		Engine::Physics::IController* _controller;
	};
}
