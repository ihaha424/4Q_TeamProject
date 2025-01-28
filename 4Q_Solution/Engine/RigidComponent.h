#pragma once

namespace Engine::Component
{
	class RigidComponent : public Component
	{
	public:
		RigidComponent();

		void Setup(Modules modules) override;

		void Initialize() override;
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
