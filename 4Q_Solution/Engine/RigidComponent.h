#pragma once

namespace Engine::Component
{
	class RigidComponent : public Component
	{
	public:
		RigidComponent();

		void Initialize(const Modules& modules) override;
		void Attach() override;
		void Update(float deltaTime) override;
		void FixedUpdate() override;
		void Detach() override;
		void Finalize() override;

	public:
		Engine::Physics::IRigidComponent* _rigidComponent;
		Engine::Physics::Manager* _physicsManager;
	};
}
