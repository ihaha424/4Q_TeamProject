#pragma once

class TriggerBox
	: public Engine::Component::Component
{
	using InteractionFunction = std::function<void(void)>;
public:
	TriggerBox();
	virtual ~TriggerBox();

	void BindBeginInteraction(const InteractionFunction& callback);
	void BindEndInteraction(const InteractionFunction& callback);

	void Initialize(const Engine::Modules& modules) override;
	void FixedUpdate() override;
	void Finalize()override;

public:
	Engine::Physics::IRigidStaticComponent* _triggerBox;

private:
	InteractionFunction _begineFunction;
	InteractionFunction _endFunction;
};

