#pragma once

namespace Engine::Component
{
	class Rigid : public Component
	{
	public:
		Rigid();

		void Initialize(const Modules& modules) override;
		void Attach() override;
		void Update(float deltaTime) override;
		void FixedUpdate() override;
		void Detach() override;
		void Finalize() override;

	public:
		Engine::Physics::IRigidComponent* _rigidbody;
		Engine::Physics::IRigidComponent* _boundBox;
	};
}
