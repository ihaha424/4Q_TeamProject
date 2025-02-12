#pragma once
#include "TriggerArea.h"

class Trigger_Sudium_SoundTrigger_2 : public TriggerArea
{
public:
	explicit Trigger_Sudium_SoundTrigger_2(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Trigger_Sudium_SoundTrigger_2() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;
	void DisposeComponents() override;

	void TriggerEvent(const PlayMsg::TriggerObject* msg);
protected:
	void PreInitialize(const Engine::Modules& modules) override;
	void PostInitialize(const Engine::Modules& modules) override;
	Engine::Component::Synchronize* _sync;
	Engine::Component::EffectSound* _soundLeft;
};

