#pragma once

namespace Engine::Component
{
	class RigidDynamic : public Component
	{
	public:
		RigidDynamic();

		void Initialize(const Modules& modules) override;
		void Attach() override;
		void Update(float deltaTime) override;
		void FixedUpdate() override;
		void Detach() override;
		void Finalize() override;

	public:
		Engine::Physics::IRigidDynamicComponent* _rigidbody;
		Engine::Physics::IRigidComponent* _boundBox;
	};
}
