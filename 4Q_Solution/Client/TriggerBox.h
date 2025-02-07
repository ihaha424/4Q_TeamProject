#pragma once
class TriggerBox
	: public Engine::Component::Component
{
public:
	TriggerBox();

	void Initialize(const Engine::Modules& modules) override;
	void Update(float deltaTime) override;
	void FixedUpdate() override;
	void Finalize()override;

public:
	Engine::Physics::IRigidStaticComponent* _triggerBox;
};

