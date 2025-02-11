#pragma once
#include "TriggerArea.h"

class Sudium_SoundTrigger : public TriggerArea
{
public:
	explicit Sudium_SoundTrigger(const std::filesystem::path& meshPath, const std::filesystem::path& physicsPath);
	virtual ~Sudium_SoundTrigger() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;


protected:
	void PreInitialize(const Engine::Modules& modules) override;

	static int _settingIndex;

};

