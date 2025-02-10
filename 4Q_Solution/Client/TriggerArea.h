#pragma once
#include "StaticObject.h"
#include "TriggerBox.h"

class TriggerArea
	:public StaticObject
{
public:
	explicit TriggerArea(std::filesystem::path&& meshPath, std::filesystem::path&& physicsPath);
	virtual ~TriggerArea() = default;

	void Prepare(Engine::Content::Factory::Component* componentFactory) override;

protected:
	void DisposeComponents() override;
	void PreInitialize(const Engine::Modules& modules) override;

protected:
	TriggerBox* _trigger;
};

