#pragma once

namespace Engine::Component
{
	class RigidDynamicComponent : public Component
	{
	public:
		RigidDynamicComponent();

		void Initialize(const Modules& modules) override;
		void Attach() override;
		void Update(float deltaTime) override;
		void FixedUpdate() override;
		void Detach() override;
		void Finalize() override;

	public:
		Engine::Physics::IRigidDynamicComponent* _rigidComponent;
	};
}
