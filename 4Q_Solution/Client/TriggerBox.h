#pragma once

class TriggerBox
	: public Engine::Component::Component
{
	using InteractionFunction = std::function<void(void)>;
public:
	TriggerBox();
	virtual ~TriggerBox();

	void Interaction();
	void BindInteraction(const InteractionFunction& callback);

	void Initialize(const Engine::Modules& modules) override;
	void Update(float deltaTime) override;
	void FixedUpdate() override;
	void Finalize()override;

public:
	Engine::Physics::IRigidComponent* _triggerBox;

private:
	InteractionFunction _function;
};

