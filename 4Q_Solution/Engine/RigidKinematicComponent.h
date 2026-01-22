#pragma once

namespace Engine::Component
{
	class RigidKinematic : public Component
	{
	public:
		RigidKinematic();

		void Initialize(const Modules& modules) override;
		void Attach() override;
		void Update(float deltaTime) override;
		void FixedUpdate() override;
		void Detach() override;
		void Finalize() override;

	public:
		Engine::Physics::IRigidKinematicComponent* _rigidbody;
		Engine::Physics::IRigidComponent* _boundBox;
	};
}
