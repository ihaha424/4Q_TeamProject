#pragma once

namespace Engine::Component
{
	class RigidStatic : public Component
	{
	public:
		RigidStatic();

		void Initialize(const Modules& modules) override;
		void Attach() override;
		void Update(float deltaTime) override;
		void FixedUpdate() override;
		void Detach() override;
		void Finalize() override;

	public:
		Engine::Physics::IRigidStaticComponent* _rigidbody;
		Engine::Physics::IRigidComponent* _boundBox;
	};
}
