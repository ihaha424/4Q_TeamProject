#pragma once

namespace Engine::Component
{
	class RigidKinematicComponent : public Component
	{
	public:
		RigidKinematicComponent();

		void Setup(Modules modules) override;

		void Initialize() override;
		void Attach() override;
		void Update(float deltaTime) override;
		void FixedUpdate() override;
		void Detach() override;
		void Finalize() override;

	public:
		Engine::Physics::RigidKinematicComponent* _rigidComponent;
		Engine::Physics::Manager* _physicsManager;
	};
}
