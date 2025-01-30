#pragma once

namespace Engine::Component
{
	class RigidStaticComponent : public Component
	{
	public:
		RigidStaticComponent();

		void Initialize(const Modules& modules) override;
		void Attach() override;
		void Update(float deltaTime) override;
		void FixedUpdate() override;
		void Detach() override;
		void Finalize() override;

	public:
		Engine::Physics::IRigidStaticComponent* _rigidComponent;
	};
}
